import pandas as pd
import matplotlib.pyplot as plt

def plot_from_csv(filepath, x_param, y_params, title, xlabel, ylabel, save_as=None, marks=[]):
	df = pd.read_csv(filepath)
	df = df.sort_values(by=x_param)

	plt.figure(figsize=(10,6))

	for y in y_params:
		plt.plot(df[x_param], df[y], marker='', label=y)

	if len(marks):
		for mark in marks:
			value = df[x_param].iloc[mark]
			plt.axvline(df[x_param][mark], color='red', label=f"Arrival rate = {df[x_param][mark]}")
	
	plt.title(title)
	plt.xlabel(xlabel)
	plt.ylabel(ylabel)

	plt.grid(True)
	plt.legend()

	plt.tight_layout()

	if save_as:
		plt.savefig(save_as)
		print(f"Saved to {save_as}")
	else:
		plt.show()
	
	plt.close()

if __name__ == '__main__':
	metrics = [
		('PacketsArrived','Packets Arrived',[]), 
		('PacketsDropped','Packets Dropped',[]),
		('DropRate','Drop Rate', []),
		('AvgWaitingTime','Average Waiting Time',[]),
		('AvgDelay','Average Delay',[]),
		('AvgQueueLength','Average Queue Length',[]),
		('ServerUtilization','Server Utilization',[58]),
		('Throughput','Throughput',[]),
	]

	packetMetrics = [
		('SimTime', 'Simulation Time', [8]),
		('PacketsArrived','Packets Arrived',[]), 
		('PacketsDropped','Packets Dropped',[]),
		('DropRate','Drop Rate', []),
		('AvgWaitingTime','Average Waiting Time',[]),
		('AvgDelay','Average Delay',[]),
		('AvgQueueLength','Average Queue Length',[]),
		('ServerUtilization','Server Utilization',[58]),
		('Throughput','Throughput',[]),
	]

	# Increasing Arrival Rate
	for metric in metrics:
		plot_from_csv(
			filepath="./outputs/incArrivalRate.csv",
			x_param="ArrivalRate",
			y_params=[metric[0]],
			title=f"{metric[1]} as Arrival Rate increases",
			xlabel="Arrival Rate",
			ylabel=metric[1],
			save_as=f"./graph/incArrivalRate/{metric[0]}.jpg"
			# marks=metric[2]
		)

	# Increasing Service Rate
	for metric in metrics:
		plot_from_csv(
			filepath="./outputs/incServiceRate.csv",
			x_param="ServiceRate",
			y_params=[metric[0]],
			title=f"{metric[1]} as Service Rate increases",
			xlabel="Service Rate",
			ylabel=metric[1],
			save_as=f"./graph/incServiceRate/{metric[0]}.jpg"
			# marks=metric[2]
			)

	# Increasing Server number
	for metric in metrics:
		plot_from_csv(
			filepath="./outputs/incServers.csv",
			x_param="Servers",
			y_params=[metric[0]],
			title=f"{metric[1]} as Servers increases",
			xlabel="Servers",
			ylabel=metric[1],
			save_as=f"./graph/incServers/{metric[0]}.jpg"
			# marks=metric[2]
			)

	# Increasing Buffer Limit
	for metric in metrics:
		plot_from_csv(
			filepath="./outputs/incBufferLimit.csv",
			x_param="BufferLimit",
			y_params=[metric[0]],
			title=f"{metric[1]} as Buffer Limit increases",
			xlabel="Buffer Limit",
			ylabel=metric[1],
			save_as=f"./graph/incBufferLimit/{metric[0]}.jpg"
			# marks=metric[2]
			)

	# Increasing Packets Served
	for metric in packetMetrics:
		plot_from_csv(
			filepath="./outputs/incPackets.csv",
			x_param="PacketsServed",
			y_params=[metric[0]],
			title=f"{metric[1]} as Packets Served increases",
			xlabel="Packets Served",
			ylabel=metric[1],
			save_as=f"./graph/incPackets/{metric[0]}.jpg"
			# marks=metric[2]
			)