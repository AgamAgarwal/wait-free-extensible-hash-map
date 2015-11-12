import sys
import sys
import numpy
from matplotlib import pyplot
from subprocess import call

FOLDER = "output/"
ITER = 10
MU = 10

def read_times(filename):
	data = []
	f = open(filename, "r")
	for line in f:
		data.append(int(line[:-1]))
	return data

def mean(l):
	return float(sum(l))/len(l)

def arr_mean(arr):
	m = []
	for x in arr:
		m.append(mean(x))
	return m

def analyze(n):
	f = open("in", "w")
	f.write(str(n)+" "+str(n)+" "+str(n)+" "+str(ITER)+" "+str(MU)+"\n")
	f.close()

	while call(["./main", "in"]) != 0:
		print "retrying", n

	wp = []
	wg = []
	wr = []
	lp = []
	lg = []
	lr = []
	for i in range(n):
		wp.extend(read_times(FOLDER + 'wait_free_put_' + str(i) + '.out'))
		wg.extend(read_times(FOLDER + 'wait_free_get_' + str(i) + '.out'))
		wr.extend(read_times(FOLDER + 'wait_free_remove_' + str(i) + '.out'))
		lp.extend(read_times(FOLDER + 'lock_based_put_' + str(i) + '.out'))
		lg.extend(read_times(FOLDER + 'lock_based_get_' + str(i) + '.out'))
		lr.extend(read_times(FOLDER + 'lock_based_remove_' + str(i) + '.out'))

	return [wp, wg, wr], [lp, lg, lr]

def main():
	wf = []
	lb = []
	cases = range(10, 51, 10)
	times = 1
	for n in cases:
		data_w = []
		data_l = []
		for t in range(times):
			print "Threads = ", n
			w, l=analyze(n)
		wf.append(arr_mean(w))
		lb.append(arr_mean(l))

	wf = numpy.array(wf)
	lb = numpy.array(lb)

	ops = ['put', 'get', 'remove']

	for i in range(3):
		wf_plot,=pyplot.plot(cases, wf[:, i], 'r')
		lb_plot,=pyplot.plot(cases, lb[:, i], 'b')
		pyplot.xticks(cases)
		pyplot.xlabel('Number of threads')
		pyplot.ylabel('Average time for ' + ops[i] + ' operation')
		pyplot.legend([wf_plot, lb_plot], ['Wait-free Extensible HashMap', 'Lock-based Extensible HashMap'])
		pyplot.show()

if __name__=="__main__":
	main()
