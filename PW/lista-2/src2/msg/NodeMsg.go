package msg

type NodeMsgType int

const (
	Reserve NodeMsgType = iota
	MoveIn  NodeMsgType = iota
	MoveOut NodeMsgType = iota

	DangerOut NodeMsgType = iota

	LocatorIn  NodeMsgType = iota
	LocatorOut NodeMsgType = iota
)

type NodeMsg struct {
	NodeMsgType NodeMsgType
	From        [2]int
	To          [2]int
	Id          int
	Resp        chan bool
}
