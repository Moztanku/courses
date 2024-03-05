package camera

import (
	constants "lista-2/src/Constants"
	types "lista-2/src/Types"
	"time"
)

type Request = types.Request
type Pos = types.Pos
type Move struct {
	From Pos
	To   Pos
}

func Camera(req_chan chan Request) {
	const (
		update_rate_ms = 1000
	)

	idMap := make(map[types.ID]types.Pos)
	dangerMap := make(map[types.Pos]bool)

	for {
		time.Sleep(time.Millisecond * time.Duration(update_rate_ms))

		moveArr := make([]Move, 0)

	end:
		for {
			select {
			case req := <-req_chan:
				if req.Id == types.Danger {
					if req.Type == types.Destroy {
						dangerMap[req.From] = false
					} else {
						dangerMap[req.From] = true
					}
				}

				if req.Type == types.Destroy {
					delete(idMap, req.Id)
					continue
				}

				if req.Type != types.MoveIn && req.Type != types.Created {
					continue
				}

				idMap[req.Id] = req.To
				moveArr = append(moveArr, Move{req.From, req.To})
			default:
				break end
			}
		}

		width := constants.WIDTH
		height := constants.HEIGHT

		rowWidth := width*4 + (width-1)*2 + 1
		rowHeight := 2

		char_arr := make([]rune, rowWidth*rowHeight*height)

		for i := 0; i < len(char_arr); i++ {
			char_arr[i] = ' '
		}

		for y := 0; y < height; y++ {
			char_arr[rowWidth-1+y*rowWidth*rowHeight] = '\n'
			char_arr[rowWidth-1+y*rowWidth*rowHeight+rowWidth] = '\n'
		}

		for x := 0; x < width; x++ {
			for y := 0; y < height; y++ {
				char_arr[y*rowWidth*rowHeight+x*6] = '['
				char_arr[y*rowWidth*rowHeight+x*6+3] = ']'
			}
		}

		for id, pos := range idMap {
			runes := int2runes(int(id))
			pos := pos.X*6 + pos.Y*rowWidth*rowHeight

			char_arr[pos+1] = runes[0]
			char_arr[pos+2] = runes[1]
		}

		for pos, isDanger := range dangerMap {
			if !isDanger {
				continue
			}

			runes := int2runes(int(types.Danger))

			pos := pos.X*6 + pos.Y*rowWidth*rowHeight

			char_arr[pos+1] = runes[0]
			char_arr[pos+2] = runes[1]
		}

		for _, move := range moveArr {
			from := move.From
			to := move.To

			if from.X == to.X && from.Y == to.Y {
				continue
			}

			if from.X-to.X == 1 {
				// Move left
				pos := from.X*6 - 2 + from.Y*rowWidth*rowHeight
				char_arr[pos] = '<'
				if char_arr[pos+1] == ' ' {
					char_arr[pos+1] = '-'
				}
			} else if from.X-to.X == -1 {
				// Move right
				pos := from.X*6 + 5 + from.Y*rowWidth*rowHeight
				char_arr[pos] = '>'
				if char_arr[pos-1] == ' ' {
					char_arr[pos-1] = '-'
				}
			} else if from.Y-to.Y == 1 {
				// Move up
				char_arr[from.X*6+1+from.Y*rowWidth*rowHeight-rowWidth] = '^'
			} else if from.Y-to.Y == -1 {
				// Move down
				char_arr[from.X*6+2+from.Y*rowWidth*rowHeight+rowWidth] = 'v'
			}
		}

		clear()
		print(string(char_arr))
	}
}

func int2runes(i int) [2]rune {
	switch i {
	case int(types.Empty):
		return [2]rune{' ', ' '}
	case int(types.Locator):
		return [2]rune{' ', '*'}
	case int(types.Danger):
		return [2]rune{' ', '#'}
	default:
		if i < 10 {
			return [2]rune{' ', rune(i + 48)}
		} else {
			return [2]rune{rune(i/10 + 48), rune(i%10 + 48)}
		}
	}
}

func clear() {
	print("\033[H\033[2J")
}
