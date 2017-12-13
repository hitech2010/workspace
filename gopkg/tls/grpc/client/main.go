package main

import (
	"context"
	"log"

	pb "github.com/warm3snow/workspace/gopkg/tls/grpc/protos"
	"google.golang.org/grpc"
)

const (
	addr = "localhost:8080"
)

func main() {
	conn, err := grpc.Dial(addr, grpc.WithInsecure())
	if err != nil {
		log.Fatalf("failed to Dail: %v", err)
	}
	defer conn.Close()
	c := pb.NewGreeterClient(conn)

	r, err := c.SayHello(context.Background(), &pb.HelloRequest{Name: "bill"})
	if err != nil {
		log.Fatalf("failed to SayHello: %v", err)
	}
	log.Printf("Greeting: %s", r.Message)
}
