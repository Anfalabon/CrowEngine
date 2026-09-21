# Stage 1: Build stage
FROM ubuntu:latest AS build

# Install build-essential for compiling C++ code
RUN apt-get update && apt-get install -y build-essential

# Set the working directory
WORKDIR /app

# Copy the source code into the container
COPY testDocker.cpp .

# Compile the C++ code statically to ensure it doesn't depend on runtime libraries
RUN g++ -o testDocker testDocker.cpp -static

# Stage 2: Runtime stage
FROM scratch

# Copy the static binary from the build stage
COPY --from=build /app/testDocker /testDocker

# Command to run the binary
CMD ["/testDocker"]