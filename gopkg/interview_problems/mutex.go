package main

import (
	"fmt"
	"strconv"
	"sync"
)

type UserAges struct {
	ages map[string]int
	sync.Mutex
}

func (this *UserAges) Add(name string, age int) {
	this.Lock()
	defer this.Unlock()
	this.ages[name] = age
}

func (this *UserAges) Get(name string) int {
	if age, ok := this.ages[name]; ok {
		return age
	}
	return -1
}

func main() {
	user := &UserAges{
		ages: make(map[string]int),
	}
	var wg sync.WaitGroup
	//write
	for i := 0; i < 10; i++ {
		wg.Add(1)
		go func(i int) {
			defer wg.Done()
			user.Add("Name"+strconv.Itoa(i), 20+i)
		}(i)
	}
	//read
	for i := 0; i < 10; i++ {
		wg.Add(1)
		go func(i int) {
			defer wg.Done()
			var name string = "Name" + strconv.Itoa(i)
			fmt.Println(user.Get(name))
		}(i)
	}
	wg.Wait()
}
