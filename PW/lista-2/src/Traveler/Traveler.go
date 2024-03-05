package traveler

import (
	types "lista-2/src/Types"
	"math/rand"
	"time"
)

type Pos = types.Pos
type ID = types.ID
type Request = types.Request

func Traveler(id ID, pos Pos, requests_chan chan Request) {
	update_rate_ms := 200 + rand.Intn(400)
	resp := make(chan bool)

	for {
		time.Sleep(time.Millisecond * time.Duration(update_rate_ms))

		nextPos := getNextPos(pos)

		request := Request{From: pos, To: nextPos, Id: id, Type: types.Reserve, Resp: resp}
		requests_chan <- request

		if !<-resp {
			continue
		}

		request = Request{From: pos, To: pos, Id: id, Type: types.MoveOut, Resp: resp}
		requests_chan <- request

		if !<-resp {
			continue
		}

		request = Request{From: pos, To: nextPos, Id: id, Type: types.MoveIn, Resp: resp}
		requests_chan <- request

		if !<-resp {
			break
		}

		pos = nextPos
	}
}

func getNextPos(pos Pos) Pos {
	newPos := pos

	random := rand.Intn(4)
	switch random {
	case 0:
		newPos.X--
	case 1:
		newPos.Y++
	case 2:
		newPos.X++
	case 3:
		newPos.Y--
	}

	return newPos
}
