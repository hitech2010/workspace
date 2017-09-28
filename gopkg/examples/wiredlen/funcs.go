package wiredlen

import "fmt"

const (
	defaultValue = "hello"
)

func test(input ...string) {
	fmt.Println("input length:", len(input))
}
