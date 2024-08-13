proc test_chip {chip_name} {
    puts "Testing $chip_name"

    # Compile the source and testbench, ignoring timescale warnings
    if {[catch {exec xvlog -sv -nolog src/${chip_name}.v test/${chip_name}_tb.v} result]} {
        puts "Error compiling $chip_name: $result"
        return
    }

    # Elaborate the design
    if {[catch {exec xelab -debug typical -nolog ${chip_name}_tb -s ${chip_name}_sim} result]} {
        puts "Error elaborating $chip_name: $result"
        return
    }

    # Run the simulation
    if {[catch {exec xsim ${chip_name}_sim -nolog -runall} result]} {
        puts "Error simulating $chip_name: $result"
        return
    }

    puts "Test completed for $chip_name"
}

# Read the chip list and test each chip
set fp [open "chip_list.txt" r]
set chip_list [split [read $fp] "\n"]
close $fp

foreach chip $chip_list {
    if {$chip != ""} {
        test_chip $chip
    }
}

puts "All tests completed"