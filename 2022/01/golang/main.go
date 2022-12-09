package main

import (
	"bufio"
	"fmt"
	"os"
	"strconv"
)

func main() {
	data, err := os.Open("../input.txt")
	if (err != nil) {
		os.Exit(1)
	}

	var m int = 0
	var b int = 0

	scanner := bufio.NewScanner(data)
	for scanner.Scan() {
		line := scanner.Text()
		if line == "" {
			b = 0
			continue
		}
		n, nerr := strconv.Atoi(line)
		if nerr != nil {
			os.Exit(1)
		}
		b = b + n
		if b > m {
			m = b
		}
	}

	if scanner.Err() != nil {
		os.Exit(1)
	}

	fmt.Printf("Part 1 Solution: %d\n", m)
}
