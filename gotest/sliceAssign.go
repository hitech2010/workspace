package main

import "fmt"

func main() {
	pad1 := []byte{0x30, 0x81, 0x8c, 0x30, 0x44, 0x02, 0x20}
	pad2 := []byte{0x30, 0x44, 0x02, 0x20}
	params := make([]byte, 143)

	copy(params[0:], pad1)
	params[39] = byte(0x02)
	params[40] = byte(0x20)
	copy(params[73:], pad2)
	params[109] = byte(0x02)
	params[110] = byte(0x20)

	PrintData(params)
}

func PrintData(in []byte) {
	for i := 0; i < len(in); i++ {
		fmt.Printf("%d: %02x\n", i, in[i])
	}
	fmt.Println()
}
