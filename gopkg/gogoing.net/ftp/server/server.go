package main

import (
	"fmt"
	"net"
	"os"
)

const (
	DIR = "DIR"
	PWD = "PWD"
	CD  = "CD"
)

func main() {
	srv := ":8888"
	tcpAddr, err := net.ResolveTCPAddr("tcp", srv)
	checkErr(err)
	listener, err := net.ListenTCP("tcp", tcpAddr)
	checkErr(err)
	for {
		conn, err := listener.Accept()
		if err != nil {
			continue
		}
		go handleClient(conn)
	}
}
func handleClient(conn net.Conn) {
	defer conn.Close()
	var buf [512]byte
	for {
		n, err := conn.Read(buf[0:])
		if err != nil {
			conn.Close()
			return
		}
		s := string(buf[0:n])
		if s[0:3] == DIR {
			dirList(conn)
		} else if s[0:3] == PWD {
			pwd(conn)
		} else if s[0:2] == CD {
			chdir(conn, s[2:n])
		}
	}
}

func chdir(conn net.Conn, s string) {
	err := os.Chdir(s)
	if err == nil {
		conn.Write([]byte("OK"))
	} else {
		fmt.Println(err.Error())
		conn.Write([]byte("ERROR"))
	}
}
func pwd(conn net.Conn) {
	s, err := os.Getwd()
	if err != nil {
		conn.Write([]byte(""))
		return
	}
	conn.Write([]byte(s))
}
func dirList(conn net.Conn) {
	defer conn.Write([]byte("\r\n"))
	dir, err := os.Open(".")
	if err != nil {
		return
	}
	names, err := dir.Readdirnames(-1)
	if err != nil {
		return
	}
	for _, name := range names {
		conn.Write([]byte(name + "\r\n"))
	}
}
func checkErr(err error) {
	if err != nil {
		fmt.Println("Fatal err", err.Error())
		os.Exit(1)
	}
}
