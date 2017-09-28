package main

import (
	"fmt"
	"time"

	jwt "github.com/dgrijalva/jwt-go"
)

func main() {
	secret := []byte("jwtkey")

	claims := &jwt.StandardClaims{
		NotBefore: int64(time.Now().Unix() - 1000),
		ExpiresAt: int64(time.Now().Unix() + 1000),
		Issuer:    "test",
	}

	token := jwt.NewWithClaims(jwt.SigningMethodHS256, claims)
	ss, err := token.SignedString(secret)
	fmt.Println("Signed Token:", ss)
	t, err := jwt.Parse(ss, func(*jwt.Token) (interface{}, error) {
		return secret, nil
	})
	if err != nil {
		fmt.Println("parse failed.", err)
		return
	}
	fmt.Println("claims after parse:", t.Claims)
	fmt.Println("parse res:", t)
}
