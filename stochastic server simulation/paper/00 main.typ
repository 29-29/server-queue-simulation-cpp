// Formatting pages
#set page(
	paper: "us-legal",
	margin: (x: 0.75in, y: 1in),
	numbering: "1/1",
	number-align: right
)

// Format paragraphs
#set par(
	justify: true
)

// TITLE
#align(
	center,
	text(20pt)[#smallcaps("Simulation Study of Behavior of Discrete-Event Single Server or Multi-Server System")]
)

#align(
	center,
	text()[*Ahmad Badron*\
	BS Computer Science\
	Mindanao State University]
)

#grid(
	columns: (1cm,1fr,1cm),
	// fill: yellow,
	column-gutter: 2pt,
	[],
	[*Abstract*: #lorem(100)]
)

#show: rest => columns(2, rest)
// #set page(columns: 2)
\

= Outline
+ Introduction
+ Methods
+ Results and Discussions
+ Conclusions

#include "01 introduction.typ"
#include "02 methods.typ"
#include "03 results.typ"
#include "04 conclusion.typ"


// Appendix
// #include "appendix.typ"