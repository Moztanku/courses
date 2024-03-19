package main

import (
	"lista-2/src2/danger"
	"lista-2/src2/locator"
	"lista-2/src2/node"
	"lista-2/src2/traveler"
)

type Traveler = traveler.Traveler
type Locator = locator.Locator
type Danger = danger.Danger
type Node = node.Node

func main() {
	nodeArray := make([]Node, 0)

	travelerArray := make([]Traveler, 0)
	dangerArray := make([]Danger, 0)
	locatorArray := make([]Locator, 0)
}
