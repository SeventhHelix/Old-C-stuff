void read3(void) {
	int size = 50;
	// size of the array
	int next_index = 0;
	// where the next number goes
	int *numbers = malloc(size * sizeof(int));
	while (has_next()) {
		if (next_index == size) {
			size *= 2;
			numbers = realloc(numbers, size*sizeof(int));
			if (numbers == NULL) abort(); // error
		}
		numbers[next_index] = read_nat();
		next_index++;
	}
}

