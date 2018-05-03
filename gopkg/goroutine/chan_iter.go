package main

import "fmt"

type container struct {
	items []item
}
type item int

func (c *container) Iter() <-chan item {
	ch := make(chan item)
	go func() {
		for i := 0; i < len(c.items); i++ {
			ch <- c.items[i]
		}
	}()
	return ch
}

func main() {
	c := &container{[]item{1, 2, 3, 4}}
	for x := range c.Iter() {
		fmt.Println(x)
	}
}
