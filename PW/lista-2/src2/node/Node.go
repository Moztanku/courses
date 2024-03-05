package node

import (
	"lista-2/src2/msg"
	"math/rand"
	"time"
)

type VisitorType = msg.SchedulerMsgTarget

type Node struct {
	Pos      [2]int
	Locator  VisitorType
	Reserved bool
	InReq    chan msg.NodeMsg
}

func (n Node) Run(scheduler_req chan msg.SchedulerMsg, visitor_msg chan msg.VisitorMsg) {
	const (
		update_rate  = 100
		spawn_chance = 5
	)

	for {
		time.Sleep(time.Millisecond * update_rate)

		if !n.Reserved && n.Locator == msg.None {
			if rand.Intn(100) < spawn_chance {
				random := rand.Intn(10)

				resp := make(chan bool)
				visitorType := msg.SchedulerMsgTarget(0)

				if random < 6 {
					visitorType = msg.Traveler
				} else if random < 9 {
					visitorType = msg.Danger
				} else {
					visitorType = msg.Locator
				}

				scheduler_req <- msg.SchedulerMsg{msg.Create, visitorType, n.Pos, resp}

				if <-resp {
					n.Locator = visitorType
					n.Reserved = true
				}
			}
		}

		select {
		case req := <-n.InReq:
			switch n.Locator {
			case msg.Traveler:
			case msg.Danger:
			case msg.Locator:

			case msg.None:
				switch req.NodeMsgType {
				case msg.Reserve:
					n.Reserved = true
					req.Resp <- true
				default:
					req.Resp <- false
					continue
				}
			}
		default:
			continue
		}
	}
}
