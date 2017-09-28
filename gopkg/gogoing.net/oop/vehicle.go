package main

import "fmt"

type HornSounder interface {
	SoundHorn()
}
type Vehicle struct {
	List [2]HornSounder
}

type Car struct {
	Sound string
}

func (this *Car) SoundHorn() {
	fmt.Println(this.Sound)
}

type Bike struct {
	Sound string
}

func (this *Bike) SoundHorn() {
	fmt.Println(this.Sound)
}

func main() {
	v := new(Vehicle)
	v.List[0] = &Car{"BEEP"}
	v.List[1] = &Bike{"RING"}
	for _, e := range v.List {
		e.SoundHorn()
	}
}
