#import "@preview/codelst:2.0.2": sourcecode, sourcefile
// #set page(columns: 1)
// #show: rest => rest
#align(
	center,
	text()[= Appendix]
)

// #figure(
// 	caption: "main.cpp",
// 	sourcefile(
// 		// read("../main.cpp"),
// 		// lang: "cpp"
// 	)
// )<main-cpp>

#figure(
	caption: "Simulation.h",
	sourcefile(
		read("../Simulation.h"),
		lang: "cpp",
		showrange: (18,74),
		showlines: false,
	)
)<simulation-h>

#figure(
	caption: "Simulation.cpp",
	sourcefile(
		file: "Simulation.cpp",
		read("../Simulation.cpp"),
		lang: "cpp",
		showrange: (5, 10),
	)
)<simulation-cpp>