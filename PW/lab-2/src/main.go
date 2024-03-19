package main

import (
	camera "lista-2/src/Camera"
	constants "lista-2/src/Constants"
	node "lista-2/src/Node"
	types "lista-2/src/Types"
	"math/rand"
)

type Node = node.Node
type Pos = types.Pos

func main() {
	width := constants.WIDTH
	height := constants.HEIGHT

	nodes := make([]Node, width*height)

	for y := 0; y < height; y++ {
		for x := 0; x < width; x++ {
			nodes[x+y*width] = node.NewNode(Pos{X: x, Y: y})
		}
	}

	id_chan := make(chan types.ID, constants.MAX_TRAVELERS)

	go func() {
		for i := 1; i <= constants.MAX_TRAVELERS; i++ {
			id_chan <- types.ID(i)
		}
		for {
			rand := rand.Intn(100)
			if rand < 10 {
				id_chan <- types.Danger
			} else {
				id_chan <- types.Invalid
			}
		}
	}()

	requests_chan := make(chan types.Request, 2*constants.MAX_TRAVELERS)

	for _, node := range nodes {
		go node.Run(id_chan, requests_chan)
	}

	camera_chan := make(chan types.Request, 2*constants.MAX_TRAVELERS)

	go camera.Camera(camera_chan)

	for {
		select {
		case request := <-requests_chan:
			to := request.To

			if to.X < 0 || to.X >= width || to.Y < 0 || to.Y >= height {
				request.Resp <- false
				continue
			}

			if request.Type == types.MoveIn || request.Type == types.Created || request.Type == types.Destroy {
				camera_chan <- request
			}

			nodes[to.X+to.Y*width].Req_chan <- request
		}
	}
}
