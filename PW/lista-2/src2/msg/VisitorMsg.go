package msg

type VisitorMsgType int

const (
	Destroy VisitorMsgType = iota
	Exmit   VisitorMsgType = iota
)

type VisitorMsg struct {
	VisitorMsgType VisitorMsgType
	From           [2]int
	Resp           chan bool
}
