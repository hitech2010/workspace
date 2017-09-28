package main

import (
	"fmt"
	"unsafe"
)

func main() {
	orgSlice := make([]string, 5, 8)
	orgSlice[0] = "Apple"
	orgSlice[1] = "Orange"
	orgSlice[2] = "Banana"
	orgSlice[3] = "Grape"
	orgSlice[4] = "Plum"

	InspectSlice(orgSlice)

	slice2 := orgSlice[2:4]
	InspectSlice(slice2)

	slice3 := slice2[1:cap(slice2)]
	InspectSlice(slice3)

	slice3[0] = "CHANGED"
	InspectSlice(slice3)
	InspectSlice(slice2)
}

func InspectSlice(slice []string) {
	// Capture the address to the slice structure
	address := unsafe.Pointer(&slice)

	// Capture the address where the length and cap size is stored
	lenAddr := uintptr(address) + uintptr(8)
	capAddr := uintptr(address) + uintptr(16)

	// Create pointers to the length and cap size
	lenPtr := (*int)(unsafe.Pointer(lenAddr))
	capPtr := (*int)(unsafe.Pointer(capAddr))

	// Create a pointer to the underlying array
	addPtr := (*[8]string)(unsafe.Pointer(*(*uintptr)(address)))

	fmt.Printf("Slice Addr[%p] Len Addr[0x%x] Cap Addr[0x%x]\n",
		address,
		lenAddr,
		capAddr)

	fmt.Printf("Slice Length[%d] Cap[%d]\n",
		*lenPtr,
		*capPtr)

	for index := 0; index < *lenPtr; index++ {
		fmt.Printf("[%d] %p %s\n",
			index,
			&(*addPtr)[index],
			(*addPtr)[index])
	}

	fmt.Printf("\n\n")
}
