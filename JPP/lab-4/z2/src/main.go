package main

import (
	"fmt"
	"math/rand"
	"sync"
	"time"
)

const (
	numPhilisophers = 10
	hunger          = 10
)

type Fork struct {
	sync.Mutex
}

type Philisopher struct {
	id          int
	left, right *Fork
}

func (p *Philisopher) eat() {
	fmt.Printf("Philisopher %d is eating\n", p.id)

	var duration time.Duration = time.Millisecond * time.Duration(200+rand.Intn(1000))
	time.Sleep(duration)
}

func (p *Philisopher) think() {
	fmt.Printf("Philisopher %d is thinking\n", p.id)

	var duration time.Duration = time.Millisecond * time.Duration(200+rand.Intn(500))
	time.Sleep(duration)
}

func (p *Philisopher) done(wg *sync.WaitGroup) {
	fmt.Printf("Philisopher %d is done\n", p.id)
	wg.Done()
}

func (p *Philisopher) task(wg *sync.WaitGroup) {
	for i := 0; i < hunger; i++ {
		p.left.Lock()
		p.right.Lock()

		p.think()

		p.right.Unlock()
		p.left.Unlock()

		p.eat()
	}

	p.done(wg)
}

func main() {
	forks := make([]*Fork, numPhilisophers)

	for i := 0; i < numPhilisophers; i++ {
		forks[i] = new(Fork)
	}

	philisophers := make([]*Philisopher, numPhilisophers)
	for i := 0; i < numPhilisophers; i++ {
		philisophers[i] = &Philisopher{
			id:    i,
			left:  forks[i],
			right: forks[(i+1)%numPhilisophers],
		}
	}

	var wg sync.WaitGroup
	wg.Add(numPhilisophers)

	for i := 0; i < numPhilisophers; i++ {
		go philisophers[i].task(&wg)
	}

	wg.Wait()
}
