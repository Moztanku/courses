package node

import (
	traveler "lista-2/src/Traveler"
	types "lista-2/src/Types"
	"math/rand"
	"time"
)

type Pos = types.Pos
type ID = types.ID
type Request = types.Request

type Node struct {
	pos      Pos
	id       ID
	taken    bool
	Req_chan chan Request
}

func (n Node) GetPos() Pos {
	return n.pos
}

func NewNode(pos Pos) Node {
	return Node{pos: pos, id: types.Empty, taken: false, Req_chan: make(chan Request)}
}

func (n Node) Run(id_chan chan ID, requests_chan chan Request) {
	update_rate_ms := 100 + rand.Intn(200)
	traveler_chance := rand.Intn(5)

	for {
		time.Sleep(time.Millisecond * time.Duration(update_rate_ms))

		// If node is empty, create a new visitor
		if rand.Intn(100) < traveler_chance && !n.taken {
			newID := <-id_chan

			if newID == types.Invalid {
				continue
			}

			n.id = newID
			if n.id == types.Danger {
				n.taken = false
			} else {
				n.taken = true
			}

			switch n.id {
			case types.Locator:
				// TODO: Implement locator
			case types.Danger:
				// TODO: Implement danger
			default:
				go traveler.Traveler(n.id, n.pos, requests_chan)
			}

			requests_chan <- Request{From: n.pos, To: n.pos, Id: n.id, Type: types.Created, Resp: make(chan bool)}
		}

		select {
		case request := <-n.Req_chan:
			switch request.Type {
			case types.Reserve:
				if n.taken {
					request.Resp <- false
				} else {
					n.taken = true
					request.Resp <- true
				}
			case types.MoveOut:
				if n.id != request.Id {
					request.Resp <- false
				} else {
					n.taken = false
					n.id = types.Empty
					request.Resp <- true
				}
			case types.MoveIn:
				if !n.taken || n.id == types.Danger {
					request.Resp <- false
					requests_chan <- Request{From: n.pos, To: n.pos, Id: n.id, Type: types.Destroy, Resp: make(chan bool)}
				} else {
					n.id = request.Id
					request.Resp <- true
				}
			case types.Destroy:
				if n.id != request.Id {
					request.Resp <- false
				} else {
					n.taken = false
					n.id = types.Empty
					request.Resp <- true
				}
			}
		default:
			continue
		}
	}
}
