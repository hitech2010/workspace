package main

import "fmt"

//Animal
type Animal struct {
	Name string
	mean bool
}
type AnimalSounder interface {
	MakeNoise()
}

//Cat
type Cat struct {
	Animal
	Strength int
}

//Dog
type Dog struct {
	Animal
	Strength int
}

//main test
func main() {
	cat := &Cat{
		Animal{
			"MIMI",
			true,
		},
		2,
	}
	dog := &Dog{
		Animal{
			"Jack",
			false,
		},
		3,
	}
	MakeSomeNoise(cat)
	MakeSomeNoise(dog)
}

func (this *Animal) MakeNoise(strength int, sound string) {
	if this.mean {
		strength = strength * 5
	}
	for i := 0; i < strength; i++ {
		fmt.Printf("%s ", sound)
	}
	fmt.Println()
}
func (this *Cat) MakeNoise() {
	this.Animal.MakeNoise(this.Strength, "MEOW")
}
func (this *Dog) MakeNoise() {
	this.Animal.MakeNoise(this.Strength, "BARK")
}

//logic
func MakeSomeNoise(animalSounder AnimalSounder) {
	animalSounder.MakeNoise()
}
