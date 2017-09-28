package main

import (
	"bytes"
	"encoding/json"
	"fmt"
)

func main() {
	jsonStr := `{"\"name\"": "\"xym\"","\"sex\"": "\"male\""}`
	var strMap map[string]interface{}

	if err := json.Unmarshal([]byte(jsonStr), &strMap); err != nil {
		panic(err)
	} else {
		fmt.Printf("%v\n", strMap)
	}

	var buf bytes.Buffer
	buf.Write([])
}
