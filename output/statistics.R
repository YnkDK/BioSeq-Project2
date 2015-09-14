require(ggplot2)
# Read the statistics for computing S
data <- read.table("compute_s.stat", sep = "\t", header = TRUE)
# Format the data
data$Algorithm <- factor(data$Algorithm)
data$n <- strtoi(data$n) - 1 # Note that we made a mistake! Our algorithms returns n + 1
data$m <- strtoi(data$m) - 1
data$CPU.clock <- strtoi(data$CPU.clock)
data$nm <- data$n * data$m

data$rank <- rank(data$CPU.clock)

# Prepare the output - Use the standard A4 size (in inches)
pdf(width = 11.69, height = 8.27)
# Plot the running times of (n*m, time/n*m) - which in our case in n^2
ggplot(data, aes(nm, CPU.clock/nm, color = Algorithm)) + 
  geom_point() +
  stat_summary(fun.y=median, geom="line") +
  ylab("CPU clock / nm")

ggplot(data, aes(nm, CPU.clock, color = Algorithm)) + 
  geom_point() +
  stat_summary(fun.y=median, geom="line") +
  ylab("CPU clock")


data <- subset(data, n >= 10000)
# Plot two boxplots next to each other
ggplot(data, aes(Algorithm, rank), color = Algorithm) + 
  geom_boxplot() +
  ylab("Ranking of CPU clock (lowest is fastest)")

# Read the statistics for finding an alignment
data <- read.table("find_alignment.stat", sep = "\t", header = TRUE)

data$Algorithm <- factor(data$Algorithm)
data$n <- strtoi(data$n) - 1
data$m <- strtoi(data$m) - 1
# Remove the noisy first measurements
data <- subset(data, n >= 10000)
data$nm <- data$n * data$m
data$CPU.clock <- strtoi(data$CPU.clock)
# Rank the running times
data$rank <- rank(data$CPU.clock)
# Plot two boxplots next to each other
ggplot(data, aes(Algorithm, rank), color = Algorithm) + 
  geom_boxplot() +
  ylab("Ranking of CPU clock (lowest is fastest)")

ggplot(data, aes(nm, CPU.clock, color = Algorithm)) + 
  geom_point() +
  stat_summary(fun.y=median, geom="line") +
  ylab("CPU clock")
# Close the PDF-file
dev.off()