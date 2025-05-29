#import "@preview/bamdone-ieeeconf:0.1.1": *

#show: ieee.with(
  title: [Simulation Study of Behavior of Discrete-Event Single Server or Multi-Server System],
  abstract: [
    #lorem(100)
  ],
authors: (
    (
      given: "Ahmad",
      surname: "Badron",
      email: [],
      affiliation: 1
    ),
  ),
  affiliations: (
    (
      name: [College of Information and Computing Sciences, Mindanao State University],
      address: [Marawi City, Lanao del Sur],
      email-suffix: [msumain.edu.ph],
    ),
  ),
  // index-terms: (),
  bibliography: bibliography("refs.bib"),
  draft: true,               // Adds the draft markers on the footer and header
  paper-size: "us-legal",
  disclaimer: none
)

#include "../paper/01 introduction.typ"
#include "../paper/02 methods.typ"
#include "../paper/03 results.typ"
#include "../paper/04 conclusion.typ"
// #include "../paper/appendix.typ"
