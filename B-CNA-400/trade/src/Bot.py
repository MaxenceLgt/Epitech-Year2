import sys
import math
import BotState as bs

class Bot:
    def __init__(self):
        self.botState = bs.BotState()
        self.stop_loss_threshold = 0.95
        self.take_profit_threshold = 1.05
        self.transaction_fee = 0.001

    def run(self):
        while True:
            reading = input()
            if len(reading) == 0:
                continue
            self.parse(reading)

    def parse(self, info: str):
        tmp = info.split(" ")
        if tmp[0] == "settings":
            self.botState.update_settings(tmp[1], tmp[2])
        if tmp[0] == "update":
            if tmp[1] == "game":
                self.botState.update_game(tmp[2], tmp[3])
        if tmp[0] == "action":
            self.make_actions()

    def make_actions(self):
        dollars = self.botState.stacks["USDT"]
        btc = self.botState.stacks["BTC"]
        close = self.botState.charts["USDT_BTC"].closes[-1]
        affordable = (dollars / close) * (1 - self.transaction_fee)
        print(f'My stacks are {dollars}. The current closing price is {close}. So I can afford {affordable}', file=sys.stderr)

        if self.should_buy() and affordable > 0:
            amount_to_buy = min(affordable, dollars * 0.1 / close)
            if amount_to_buy > 0:
                self.botState.last_buy_price = close
                print(f'buy USDT_BTC {amount_to_buy}', flush=True)
        elif self.should_sell() and btc > 0:
            amount_to_sell = btc * 0.1
            if amount_to_sell > 0:
                print(f'sell USDT_BTC {amount_to_sell}', flush=True)
        elif self.stop_loss_reached(close, btc) and btc > 0:
            print(f'sell USDT_BTC {btc}', flush=True)
        elif self.take_profit_reached(close, btc) and btc > 0:
            print(f'sell USDT_BTC {btc}', flush=True)
        else:
            print(f"pass", flush=True)

    def stop_loss_reached(self, current_price, btc):
        if btc == 0 or not hasattr(self.botState, 'last_buy_price'):
            return False
        stop_loss_price = self.botState.last_buy_price * self.stop_loss_threshold
        stop_loss_hit = current_price <= stop_loss_price
        if stop_loss_hit:
            print(f'Stop loss hit: current price {current_price} <= stop loss price {stop_loss_price}', file=sys.stderr)
        return stop_loss_hit

    def take_profit_reached(self, current_price, btc):
        if btc == 0 or not hasattr(self.botState, 'last_buy_price'):
            return False
        take_profit_price = self.botState.last_buy_price * self.take_profit_threshold
        take_profit_hit = current_price >= take_profit_price
        if take_profit_hit:
            print(f'Take profit hit: current price {current_price} >= take profit price {take_profit_price}', file=sys.stderr)
        return take_profit_hit
                
    def should_buy(self):
        buy_signal = self.bollinger_bands() == "buy" and self.rsi() == "buy"
        if buy_signal:
            print('Buy signal detected', file=sys.stderr)
        return buy_signal
        
    def should_sell(self):
        sell_signal = self.bollinger_bands() == "sell" and self.rsi() == "sell"
        if sell_signal:
            print('Sell signal detected', file=sys.stderr)
        return sell_signal

    def bollinger_bands(self):
        closes = self.botState.charts["USDT_BTC"].closes[-24:]
        if len(closes) < 24:
            return "no_moves"

        SAM = sum(closes) / len(closes)
        variance = sum((close - SAM) ** 2 for close in closes) / len(closes)
        std_dev = math.sqrt(variance)
        upper = SAM + 2 * std_dev
        lower = SAM - 2 * std_dev
        close = closes[-1]

        print(f'Bollinger Bands: CLOSE: {close}, LOWER: {lower}, UPPER: {upper}', file=sys.stderr, flush=True)
        
        if close >= upper:
            return "sell"
        elif close <= lower:
            return "buy"
        else:
            return "no_moves"

    def rsi(self):
        closes = self.botState.charts["USDT_BTC"].closes[-24:]
        if len(closes) < 24:
            return "no_moves"

        gains = []
        losses = []
        for i in range(1, len(closes)):
            change = closes[i] - closes[i - 1]
            if change > 0:
                gains.append(change)
            else:
                losses.append(abs(change))

        avg_gain = sum(gains) / len(gains) if gains else 0
        avg_loss = sum(losses) / len(losses) if losses else 1
        rs = avg_gain / avg_loss
        rsi = 100 - (100 / (1 + rs))

        print(f'RSI: {rsi}', file=sys.stderr, flush=True)
        
        if rsi < 30:
            return "buy"
        elif rsi > 70:
            return "sell"
        else:
            return "no_moves"
