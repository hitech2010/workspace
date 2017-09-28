package main

type student struct {
	Name string
	Age  int
}

func pase_student() {
	m := make(map[string]*student)
	stus := []student{
		student{"zhou", 24},
		student{"li", 24},
		student{"wang", 24},
	}
	for _, stu := range stus {
		m[stu.Name] = &stu
	}
}

func main() {

}
