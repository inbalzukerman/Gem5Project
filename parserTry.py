
with open('log.txt') as f:
	lines = f.readlines()

	splitLines = [line.split() for line in lines]

	times =[]


	for lineNum in range(len(splitLines)):
		for line2Num in range(lineNum+1, len(splitLines)):

			if splitLines[lineNum][0] == 'Access' and splitLines[line2Num][0] == 'Answer':
				if splitLines[lineNum][1] == splitLines[line2Num][1] and splitLines[lineNum][4] == splitLines[line2Num][4]:
					print int(splitLines[line2Num][6]) - int(splitLines[lineNum][6])

					break

