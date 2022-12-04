import numpy as np
import matplotlib.pyplot as plt
from pandas_datareader import data
import pandas_datareader.data as web
import pandas_datareader.data as webdata
import pandas as pd
import seaborn as sns
import matplotlib.patches as mpatches
tickers = ['F','TSLA','FSR','GM','NEE','SO','BYD','NIO','SOL','JKS']
startDate = '2019-01-01'
endDate = '2022-12-02'

def getMaxDrawDown(x):
    j = np.argmax((np.maximum.accumulate(x) - x) / x)
    if j == 0:
        return 0
    i = np.argmax(x[:j])
    d = (x[i] - x[j]) / x[i] * 100
    return d

if __name__ == "__main__":
    F = webdata.get_data_stooq('F', startDate, endDate)
    TSLA = webdata.get_data_stooq('TSLA', startDate, endDate)
    FSR = webdata.get_data_stooq('FSR', startDate, endDate)
    GM = webdata.get_data_stooq('GM', startDate, endDate)
    NEE = webdata.get_data_stooq('NEE', startDate, endDate)
    SO = webdata.get_data_stooq('SO', startDate, endDate)
    BYD = webdata.get_data_stooq('BYD', startDate, endDate)
    NIO = webdata.get_data_stooq('NIO', startDate, endDate)
    SOL = webdata.get_data_stooq('SOL', startDate, endDate)
    JKS = webdata.get_data_stooq('JKS', startDate, endDate)

    stocks = pd.DataFrame({
        "F": F["Close"],
        "TSLA": TSLA["Close"],
        "FSR": FSR["Close"],
        "GM": GM["Close"],
        "NEE":NEE["Close"],
        "SO":SO["Close"],
        "BYD":BYD["Close"],
        "NIO":NIO["Close"],
        "SOL":SOL["Close"],
        "JKS":JKS["Close"],
    })

    # print(stocks)

    plt.style.use('ggplot')
    color_palette = sns.color_palette("hls", 10)
    # plt.rcParams['font.sans-serif'] = ['Times New Roman']
    fig = plt.figure(figsize=(16,12))
    for i,j in enumerate(tickers):
        plt.subplot(5, 2, i+1)
        stocks[j].plot(kind='line', style=['-'], color=color_palette[i],label=j)
        plt.xlabel('')
        plt.ylabel('closing prices')
        plt.title('{} - closing prices Plot'.format(j))
        plt.legend()
    plt.tight_layout()
    plt.show()

    plt.style.use('ggplot')
    color_palette = sns.color_palette("hls", 10)
    # plt.rcParams['font.sans-serif'] = ['']
    fig = plt.figure(figsize=(16,12))
    for i,j in enumerate(tickers):
        plt.subplot(5,2,i+1)
        stocks[j].pct_change().plot(kind='line', style=['-'], color=color_palette[i], label=j)
        plt.xlabel('')
        plt.ylabel('percentage')
        plt.title('{} - Percentage change of closing price'.format(j))
        plt.legend()
    plt.tight_layout()
    plt.show()

    for i in tickers:
        r_daily_mean = ((1+stocks[i].pct_change()).prod())**(1/stocks[i].shape[0]) -1
        print("%s - Average daily return is: %s" % (i, str(round(r_daily_mean*100, 2)) + "%"))

    plt.style.use('ggplot')
    fig = plt.figure(figsize=(16,12))
    for i,j in enumerate(tickers):
        plt.subplot(5,2,i+1)
        sns.distplot(stocks[j].pct_change(), bins=100, color=color_palette[i])
        plt.ylabel('Daily Return')
        plt.title('{} - DailyReturn distruction'.format(j))
    plt.tight_layout()
    plt.show()

    plt.style.use('ggplot')
    fig = plt.figure(figsize=(16,12))
    for i,j in enumerate(tickers):
        plt.subplot(5,2,i+1)
        cc = (1+stocks[j].pct_change()).cumprod()
        cc.plot(kind='line', style=['-'], color=color_palette[i],label=j)
        plt.xlabel('')
        plt.title('{} - Cumulative daily return'.format(j))
        plt.legend()
    plt.tight_layout()
    plt.show()

    fig = plt.figure(figsize=(16,12))
    for i,j in enumerate(tickers):
        plt.subplot(5,2,i+1)
        daily_ret = stocks[j].pct_change()
        monthly_ret = daily_ret.resample('M').apply(lambda x : ((1+x).prod()-1))
        monthly_ret.plot(color=color_palette[i])
        startDate=monthly_ret.index[0]
        endDate=monthly_ret.index[-1]
        dateRange = pd.date_range(startDate,endDate,freq='Y')
        dateLabel = [str(y) for y in range(startDate.year,endDate.year+1)]
        print(dateRange)
        print(dateLabel)
        plt.xticks(dateRange,dateLabel)
        dates=monthly_ret[monthly_ret>monthly_ret.quantile(0.75)].index
        for i in range(0,len(dates)):
            plt.scatter(dates[i], monthly_ret[dates[i]], color='r')
        labs = mpatches.Patch(color='red', alpha=.5,label="Monthly return higher than 3/4")
        plt.title('%s - Monthly return of closing price' % j, size=15)
        plt.legend(handles=[labs])
    plt.tight_layout()
    plt.show()

    # 月平均收益
    plt.style.use('ggplot')
    fig = plt.figure(figsize=(15,15))
    for i,j in enumerate(tickers):
        plt.subplot(5,2,i+1)
        daily_ret = stocks[j].pct_change()
        monthly_ret = daily_ret.resample('M').apply(lambda x : ((1+x).prod() - 1))
        mrets = (monthly_ret.groupby(monthly_ret.index.month).mean()*100).round(2)
        attr = [str(i) + 'm' for i in range(1,13)]
        v = list(mrets)
        plt.bar(attr, v, color=color_palette[i], label=j)
        for a,b in enumerate(v):
            plt.text(a, b+0.08, b, ha='center', va='bottom')
        plt.title('{} - Average monthly return'.format(j))
        plt.legend()
    plt.tight_layout()
    plt.show()

    # CAGR
    for i in tickers:
        days = (stocks[i].index[0] - stocks[i].index[-1]).days
        CAGR_3 = (stocks[i][-1] / stocks[i][0]) ** (365/days) - 1
        print("%s (CAGR): %s" % (i, str(round(CAGR_3*100, 2)) + "%"))

    for i in tickers:
        r_daily_mean = ((1 + stocks[i].pct_change()).prod()) ** (1/stocks[i].shape[0]) - 1
        annual_rets = (1 + r_daily_mean) ** 252 - 1
        print("%s' annualized rate of return is: %s" % (i,str(round(annual_rets * 100, 2))) + "%")

    for i in tickers:
        MaxDrawDown = getMaxDrawDown(stocks[i])
        print("%s maximum drawdowns: %s" % (i, str(round(MaxDrawDown, 2)) + "%"))

