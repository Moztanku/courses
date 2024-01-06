package types

type Pos struct {
	X, Y int
}

type ID int

const (
	Empty   ID = 0
	Locator ID = -1
	Danger  ID = -2
	Invalid ID = -99
)

type Request_Type int

const (
	Reserve Request_Type = 0
	MoveOut Request_Type = 1
	MoveIn  Request_Type = 2
)

type Request struct {
	From Pos
	To   Pos
	Id   ID
	Type Request_Type
	Resp chan bool
}
