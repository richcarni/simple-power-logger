#!/usr/bin/env python3

import argparse
import pandas as pd
import matplotlib.pyplot as plt

parser = argparse.ArgumentParser()
parser.add_argument('i', type=str, help='input file')
args = parser.parse_args()

df = pd.read_csv (args.i, names = [
    'time', 'shunt voltage', 'bus voltage', 'current', 'power'
    ]
)

# df2 = df[['time','power']].loc[(df['time']>13.1) & (df['time']<580)]
df = df.loc[(df['time']<580)]

print(df)
powerSum = df['power'].sum()
currentSum =df['current'].sum()
duration = df['time'].iloc[-1] - df['time'].iloc[0]
period = df['time'].iloc[1] - df['time'].iloc[0]
print('sample period {:.3f} ms'.format(period*1000))
print('sample rate {:.1f} Hz'.format(1/period))
print('power {:.2f} mWh'.format(powerSum * (period/3600) * 1000))
print('current {:.2f} mAh'.format(currentSum * (period/3600) * 1000))

df.plot(x='time', y='power', ylim=(0,None))#, marker='o')
plt.show()
