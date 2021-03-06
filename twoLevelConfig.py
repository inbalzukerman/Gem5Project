import sys

sys.path.append("/home/sinbalzu/gem5/configs")
sys.path.append("/home/sinbalzu/gem5/configs/common")
sys.path.append("/home/sinbalzu/gem5/configs/topologies")
sys.path.append("/home/sinbalzu/gem5/configs/ruby")
sys.path.append("/home/sinbalzu/gem5/src/python/m5")

import m5
from m5.objects import *

m5.util.addToPath('../../')

import CacheConfig
import MemConfig
import Simulation
from caches import *
import common

from cpu2000 import *

# class L1ICache(L1Cache):
#    size = '32MB'

# class L1DCache(L1Cache):
#    size = '32MB'




# Set the usage message to display
SimpleOpts.set_usage("usage: %prog [options] <binary to execute>")

# Finalize the arguments and grab the opts so we can pass it on to our objects
(opts, args) = SimpleOpts.parse_args()

binary = 'm5threads/progs/prog.o'

# Check if there was a binary passed in via the command line and error if
# there are too many arguments
if len(args) == 1:
    binary = args[0]
elif len(args) > 1:
    SimpleOpts.print_help()
    m5.fatal("Expected a binary to execute as positional argument")

cpus = [DerivO3CPU(cpu_id = i) for i in xrange(4)]
workload = Process(cmd = binary) 

# Set the cpu to use the process as its workload and create thread contexts
for cpu in cpus:
    cpu.workload = workload
    #cpu.numThreads = 1
    cpu.createThreads()


system = System(cpu = cpus,
                physmem = SimpleMemory(), 
                membus = SystemXBar())

system.multi_thread = True

# Set the clock fequency of the system (and all of its children)
system.clk_domain = SrcClockDomain()
system.clk_domain.clock = '3GHz'
system.clk_domain.voltage_domain = VoltageDomain()

# Set up the system
system.mem_mode = 'timing'               # Use timing accesses
system.mem_ranges = [AddrRange('512MB')] # Create an address range


for cpu in cpus:
    cpu.icache = L1ICache(opts)
    cpu.dcache = L1DCache(opts)

    cpu.icache.cpu_side = cpu.icache_port
    cpu.dcache.cpu_side = cpu.dcache_port


system.l2bus = CoherentXBar(forward_latency = 3, frontend_latency = 3, response_latency = 3,
									  snoop_response_latency = 3, width = 32)


# Hook the CPU ports up to the l2bus
for cpu in cpus:
    cpu.icache.connectBus(system.l2bus)
    cpu.dcache.connectBus(system.l2bus)

# Create an L2 cache and connect it to the l2bus
system.l2cache = L2Cache(opts)

# Connect the L2 cache to the membus
system.l2cache.connectMemSideBus(system.membus)
system.l2cache.connectCPUSideBus(system.l2bus)

# create the interrupt controller for the CPU
for cpu in cpus:
    cpu.createInterruptController()

# For x86 only, make sure the interrupts are connected to the memory
# Note: these are directly connected to the memory bus and are not cached

if m5.defines.buildEnv['TARGET_ISA'] == "x86":
    for cpu in cpus:
        cpu.interrupts[0].pio = system.membus.master
        cpu.interrupts[0].int_master = system.membus.slave
        cpu.interrupts[0].int_slave = system.membus.master

# Connect the system up to the membus
system.system_port = system.membus.slave
system.physmem.port = system.membus.master


# set up the root SimObject and start the simulation
root = Root(full_system = False, system = system)
# instantiate all of the objects we've created above
m5.instantiate()

print "Beginning simulation!"
exit_event = m5.simulate()
print 'Exiting @ tick %i because %s' % (m5.curTick(), exit_event.getCause())