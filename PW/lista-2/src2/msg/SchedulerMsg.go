package msg

type SchedulerMsgType int

const (
	Create SchedulerMsgType = iota
	Remove SchedulerMsgType = iota
)

type SchedulerMsgTarget int

const (
	None     SchedulerMsgTarget = iota
	Traveler SchedulerMsgTarget = iota
	Danger   SchedulerMsgTarget = iota
	Locator  SchedulerMsgTarget = iota
)

type SchedulerMsg struct {
	SchedulerMsgType   SchedulerMsgType
	SchedulerMsgTarget SchedulerMsgTarget
	At                 [2]int
	Resp               chan bool
}
