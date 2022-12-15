package main

import (
	"bufio"
	"fmt"
	"os"
	"strconv"
)

func getTotalCalories(caloriesArr *[3]int) (total int) {
	total = 0
	for _, calories := range (*caloriesArr) {
		total += calories
	}
	return
}

func compareCalories(caloriesArr *[3]int, comparable int) {
	if (comparable > (*caloriesArr)[0]) {
		(*caloriesArr)[2] = (*caloriesArr)[1]
		(*caloriesArr)[1] = (*caloriesArr)[0]
		(*caloriesArr)[0] = comparable
	} else if (comparable > (*caloriesArr)[1] && comparable != (*caloriesArr)[0]) {
		(*caloriesArr)[2] = (*caloriesArr)[1]
		(*caloriesArr)[1] = comparable
	} else if (comparable > (*caloriesArr)[2] && comparable != (*caloriesArr)[1]) {
		(*caloriesArr)[2] = comparable
	}
}

func main() {
	data, err := os.Open("../input.txt")
	if (err != nil) {
		os.Exit(1)
	}

	buffer := 0
	topCalories := [3]int{0, 0, 0}

	scanner := bufio.NewScanner(data)
	for scanner.Scan() {
		line := scanner.Text()
		if line == "" {
			buffer = 0
			continue
		}
		calories, caloriesErr := strconv.Atoi(line)
		if caloriesErr != nil {
			os.Exit(1)
		}
		buffer += calories
		compareCalories(&topCalories, buffer)
	}

	if scanner.Err() != nil {
		os.Exit(1)
	}

	fmt.Printf("Part 1 Solution: %d\n", topCalories[0])
	fmt.Printf("Part 2 Solution: %d\n", getTotalCalories(&topCalories))
}
