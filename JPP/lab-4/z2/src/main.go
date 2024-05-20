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
	id            int
	lower, higher *Fork
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
		p.think()

		p.lower.Lock()
		p.higher.Lock()

		p.eat()

		p.higher.Unlock()
		p.lower.Unlock()
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

		if i != numPhilisophers-1 {
			philisophers[i] = &Philisopher{
				id:     i,
				lower:  forks[i],
				higher: forks[i+1],
			}
		} else {
			philisophers[i] = &Philisopher{
				id:     i,
				lower:  forks[0],
				higher: forks[i],
			}
		}
	}

	var wg sync.WaitGroup
	wg.Add(numPhilisophers)

	for i := 0; i < numPhilisophers; i++ {
		go philisophers[i].task(&wg)
	}

	wg.Wait()
}
