# From: https://en.wikipedia.org/wiki/Names_of_large_numbers
.numbers <- data.frame(
                name=c("Thousand", "Million", "Billion", "Trillion", "Quadrillion", "Quintillion", "Sextillion", "Septillion", "Octillion", "Nonillion", "Decillion", "Undecillion", "Duodecillion", "Tredecillion", "Quattuordecillion", "Quindecillion", "Sexdecillion", "Septendecillion", "Octodecillion", "Novemdecillion", "Vigintillion", "Googol", "Centillion"),
                shorthand=c("k", "m", "b", "t", "q", "qt", "sx", "sp", "ot", "n", "d", "u", "dd", "td", "qtd", "qd", "sxd", "spd", "otd", "nd", "vg", "g", "ct"),
                exponent=c(3, 6, 9, 12, 15, 18, 21, 24, 27, 30, 33, 36, 39, 42, 45, 48, 51, 54, 57, 60, 63, 100, 303),
                stringsAsFactors=F
)



.time <- list(
                 unit=c("seconds", "minutes", "hours", "days", "years", "centuries"),
                 factor=c(1.0, 60.0, 3600.0, 86400.0, 31557600, 3155760000)
)

