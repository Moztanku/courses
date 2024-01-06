package main

import (
	"fmt"
	"math/rand"
	"strconv"
	"strings"
	"time"
)

const (
	m = 5 // Wymiary kraty
	n = 5
)

type Traveler struct {
	id int
	x  int
	y  int

	moveChance float64
	moveInterv time.Duration
}

func getAllPossibleMoves(grid *[m][n]int, x, y int) [][2]int {
	var possibleMoves [][2]int
	if x > 0 && (*grid)[x-1][y] == 0 {
		possibleMoves = append(possibleMoves, [2]int{x - 1, y})
	}
	if x < m-1 && (*grid)[x+1][y] == 0 {
		possibleMoves = append(possibleMoves, [2]int{x + 1, y})
	}
	if y > 0 && (*grid)[x][y-1] == 0 {
		possibleMoves = append(possibleMoves, [2]int{x, y - 1})
	}
	if y < n-1 && (*grid)[x][y+1] == 0 {
		possibleMoves = append(possibleMoves, [2]int{x, y + 1})
	}

	return possibleMoves
}

func (t *Traveler) update(grid *[m][n]int, moveCh chan<- [3]int) {
	moveCh <- [3]int{t.id, t.x, t.y}

	for {
		time.Sleep(t.moveInterv)
		if rand.Float64() >= t.moveChance {
			continue
		}

		var possibleMoves [][2]int = getAllPossibleMoves(grid, t.x, t.y)
		if len(possibleMoves) == 0 {
			continue
		}

		var move [2]int = possibleMoves[rand.Intn(len(possibleMoves))]
		moveCh <- [3]int{t.id, t.x, t.y}
		moveCh <- [3]int{t.id, move[0], move[1]}
		t.x = move[0]
		t.y = move[1]
	}
}

func grid_update(grid *[m][n]int, moveCh chan<- [3]int) {
	const (
		updateRate   = 100 * time.Millisecond
		appearChance = 0.1
		maxTravelers = 10
	)

	if maxTravelers >= m*n {
		panic("Too many travelers")
	}

	var id int = 0
	var count int = 0

	for {
		time.Sleep(updateRate)
		if rand.Float64() >= appearChance || count >= maxTravelers {
			continue
		}

		var t Traveler
		t.id = id
		id++
		t.moveChance = 0.1 + rand.Float64()*0.5
		t.moveInterv = time.Duration(100+rand.Intn(501)) * time.Millisecond

		t.x = rand.Intn(m)
		t.y = rand.Intn(n)

		if grid[t.x][t.y] > 0 {
			id--
			continue
		}

		count++
		go t.update(grid, moveCh)
	}
}

func clear() {
	fmt.Print("\033[H\033[2J")
}

func intToString(i int) string {
	if i == 0 {
		return "  "
	}
	if i == -1 {
		return ".."
	}
	if i < 10 {
		return " " + strconv.Itoa(i)
	}
	return strconv.Itoa(i)
}

func camera_update(grid *[m][n]int, moveCh <-chan [3]int) {
	const (
		frameTime = 1000 * time.Millisecond
		block     = "█"
	)

	travelers := make(map[int][2]int)

	for {
		time.Sleep(frameTime)
		clear()

		arr := [m][n]int{}

	moves:
		for {
			select {
			case move := <-moveCh:
				arr[move[1]][move[2]] = -1
				travelers[move[0]] = [2]int{move[1], move[2]}
			default:
				break moves
			}
		}

		for id, pos := range travelers {
			arr[pos[0]][pos[1]] = id
		}

		fmt.Println()
		for y := 0; y < n; y++ {
			for x := 0; x < m; x++ {
				fmt.Print(intToString(arr[x][y]))
				if x != m-1 {
					fmt.Print(block)
				}
			}
			fmt.Print("\n")
			if y != n-1 {
				s := strings.Repeat(block, m*3-1)
				fmt.Println(s)
			}
		}
	}
}

func main() {
	if m >= 10 || n >= 10 {
		panic("Grid too big")
	}

	var moveChannel chan [3]int = make(chan [3]int, 100)
	var grid = [m][n]int{}

	go grid_update(&grid, moveChannel)
	camera_update(&grid, moveChannel)
}
