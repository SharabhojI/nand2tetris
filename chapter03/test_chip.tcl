proc test_chip {chip_name} {
    puts "Testing $chip_name"

    # List of chips from previous chapters that might be needed
    set prev_chips [list \
        "../chapter01/src/NAND.v" \
        "../chapter01/src/NOT.v" \
        "../chapter01/src/AND.v" \
        "../chapter01/src/OR.v" \
        "../chapter01/src/MUX.v" \
        "../chapter01/src/MUX16.v" \
        "../chapter01/src/DMUX.v" \
        "../chapter01/src/DMUX4WAY.v" \
        "../chapter01/src/DMUX8WAY.v" \
        "../chapter01/src/MUX4WAY16.v" \
        "../chapter01/src/MUX8WAY16.v" \
        "../chapter02/src/INC16.v" \
    ]

    # Compile the source, testbench, and required previous chips
    set compile_cmd "xvlog -sv -nolog src/${chip_name}.v test/${chip_name}_tb.v"
    foreach chip $prev_chips {
        append compile_cmd " $chip"
    }
    
    if {[catch {eval exec $compile_cmd} result]} {
        puts "Error compiling $chip_name: $result"
        return 0
    }

    # Elaborate the design
    if {[catch {exec xelab -debug typical -nolog ${chip_name}_tb -s ${chip_name}_sim} result]} {
        puts "Error elaborating $chip_name: $result"
        return 0
    }

    # Run the simulation
    set sim_output [exec xsim ${chip_name}_sim -nolog -runall]
    
    # Check for "Error" in simulation output
    if {[string first "Error" $sim_output] != -1} {
        puts "Test failed for $chip_name"
        puts $sim_output
        return 0
    } else {
        puts "Test passed for $chip_name"
        return 1
    }
}

# Read the chip list and test each chip
set fp [open "chip_list.txt" r]
set chip_list [split [read $fp] "\n"]
close $fp

set total_tests 0
set passed_tests 0

foreach chip $chip_list {
    if {$chip != ""} {
        incr total_tests
        if {[test_chip $chip]} {
            incr passed_tests
        }
    }
}

puts "Tests completed: $passed_tests passed out of $total_tests total tests"