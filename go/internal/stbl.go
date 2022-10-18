package main

// import (
// 	"bytes"
// 	"encoding/binary"
// 	"os"
// )

type StringEntry struct {
	Key   uint32
	Value string
}

type StringTable struct {
	Count   uint32
	Entries []StringEntry
}

// func ReadStringTable(filepath string) StringTable {
// 	file, err := os.Open(filepath)
// 	if err != nil {
// 		panic(err)
// 	}
// 	defer file.Close()

// 	buffer := bytes.NewBuffer(data)
// 	err = binary.Read(buffer, binary.LittleEndian, &header)
// 	if err != nil {
// 		panic(err)
// 	}

// 	return stbl
// }
