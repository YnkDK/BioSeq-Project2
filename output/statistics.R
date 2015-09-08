require(ggplot2)

data <- read.table("performance.stat", sep = "\t", header = TRUE)

data$Algorithm <- factor(data$Algorithm)
data$n <- strtoi(data$n)
data$n <- strtoi(data$m)
data$CPU.clock <- strtoi(data$CPU.clock)
data$nm <- data$n * data$m

ggplot(data, aes(nm, CPU.clock, color = Algorithm)) + 
  geom_point() +
  stat_summary(fun.y=median, geom="line")
