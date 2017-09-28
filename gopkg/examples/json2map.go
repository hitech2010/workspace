package main

import (
	"encoding/json"
	"fmt"
	"os"
)

func main() {
	jsonStr := "{\"name\":\"1494647507\",\"secret\":\"HSaOoFroNsWw\"}"
	var Map = make(map[string]interface{})
	err := json.Unmarshal([]byte(jsonStr), &Map)
	if err != nil {
		fmt.Println(err)
		os.Exit(-1)
	}
	fmt.Println("jsonStr: ", jsonStr)
	fmt.Println("Map: ", Map)
	for k, v := range Map {
		fmt.Println(k, v)
	}
}
