# -*- coding: utf-8 -*-
import nltk
import string
printable = set(string.printable)

filename = '6ablemen.txt'

# Using the newer with construct to close the file automatically.
with open(filename) as f:
	while True:
		chunk = f.read()
		if not chunk:
			break
		
		chunk = filter(lambda x: x in printable, chunk)

		allnouns = []
		curnouns = []
		tagged = nltk.pos_tag(nltk.word_tokenize(chunk.lower()))
		for word, tag in tagged:
			if word == "." and curnouns:
				allnouns.append(curnouns)
				curnouns = []
			elif "NN" in tag:
				curnouns.append(word)

		for sentence in allnouns:
			for noun in sentence:
				print noun,
			print ""

# nouns = [word for word,tag in nltk.pos_tag(nltk.word_tokenize(passage)) if "NN" in tag]
# print nouns

# sentences = passage.split(". ")
# for sentence in sentences:
# 	tags =  nltk.pos_tag(nltk.word_tokenize(sentence))
# 	# print tags
# 	nouns = [word for word,tag in tags if "NN" in tag]
# 	print nouns