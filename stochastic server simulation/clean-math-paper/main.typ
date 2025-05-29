#import "@preview/clean-math-paper:0.2.0": *

#let date = datetime.today().display("[month repr:long] [day], [year]")
#show: template.with(
  title: "Simulation Study of Queueing Behavior in a Discrete-Event Single Server and Multi-Server System",
  authors: (
    (name: "Ahmad Badron", affiliation-id: 1, orcid: "0000-0000-0000-0000"),
  ),
  // affiliations: (
  //   (id: 1, name: "BS Computer Science, Mindanao State University"),
  // ),
  date: date,
  heading-color: rgb("#bb0000"),
  link-color: rgb("#00f"),
  // Insert your abstract after the colon, wrapped in brackets.
  // Example: `abstract: [This is my abstract...]`
  abstract: [This paper serves to explore how a single server queueing system would behave under different parameters. In addition, it also aims to seek the most optimal scenario of a single server or multi-server system.],
  // keywords: ("First keyword", "Second keyword", "etc."),
  // AMS: ("65M70", "65M12", )
)

#include "../paper/01 introduction.typ"
#include "../paper/02 methods.typ"
#include "../paper/03 results.typ"
#include "../paper/04 conclusion.typ"
#include "../paper/appendix.typ"