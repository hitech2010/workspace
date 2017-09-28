package main

import (
	"fmt"
	"net/http"
	"os"
)

func main() {
	fileServer := http.FileServer(http.Dir("/home/hxy"))
	http.Handle("/", fileServer)
	http.HandleFunc("/js/printenv", func(w http.ResponseWriter, r *http.Request) {
		env := os.Environ()
		w.Write([]byte("<h1>Environment</h1><pre>"))
		for _, v := range env {
			w.Write([]byte(v + "\n"))
		}
		w.Write([]byte("</pre>"))
	})

	err := http.ListenAndServe(":8080", nil)
	if err != nil {
		fmt.Errorf(err.Error())
	}
}
