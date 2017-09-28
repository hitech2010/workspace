package main

import (
	"fmt"
	"net/smtp"
	"os"
	"strings"
)

/*
const (
	HOST     = "smtp.xx.com"
	PORT     = ":25"
	USER     = "xx@xx.com"
	PASSWORD = "xyz"
)
*/
type User struct {
	host     string "host"
	port     string "port"
	username string "username"
	password string "password"
}
type Email struct {
	to      string "to"
	subject string "subject"
	msg     string "msg"
}

func NewEmail(to, subj, msg string) *Email {
	return &Email{to, subj, msg}
}
func NewUser(host, port, username, password string) *User {
	return &User{host, port, username, password}
}

func SendEmail(user *User, email *Email) error {
	auth := smtp.PlainAuth("", user.username, user.password, user.host)
	//sendTo := strings.Split(email.to, ";")
	//need two \r\n before email.msg
	str := "From:" + user.username + "\r\nTo:" + email.to + "\r\nSubject:" + email.subject + "\r\nMIME-version:1.0\r\nContent-Type: text/plain;charset=UTF-8\r\n\r\n" + email.msg
	fmt.Println(str)
	err := smtp.SendMail(
		user.host+":"+user.port,
		auth,
		user.username,
		strings.Split(email.to, ";"),
		[]byte(str),
	)
	if err != nil {
		return fmt.Errorf("Failed to SendEmail [%s]", err)
	}
	return nil
}
func main() {
	//read info from stdio
	//note: to and from is a email address
	var host, port, name, passwd, to, subj, body string
	fmt.Println("Enter User[from-email passwd]")
	fmt.Scanf("%s%s\n", &name, &passwd)
	fmt.Println("Enter Email[to-email]")
	fmt.Scanf("%s\n", &to)

	host = "smtp.qq.com"
	port = "25"
	subj = "GoLang stmp Test"
	body = "hello world"
	//send email
	user := NewUser(host, port, name, passwd)
	email := NewEmail(to, subj, body)
	fmt.Println(user, email)
	if err := SendEmail(user, email); err != nil {
		fmt.Println(err)
		os.Exit(1)
	}
}
