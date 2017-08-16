# Project: Simular alcanze de nivel por usuario por cantidad de dinero
# Development: Larc Carbellido
 
# Require libraries
import csv, os, re, sys, time

# Global vars
userCur = 0
coinSave = 0
countLvl = []
countSpins = []

# Read CSV machine settings
with open('settings.csv', 'rb') as csvfile:
	reader = csv.DictReader(csvfile)
	level = []
	machine = []
	line = []
	maxBet = []
	pointRequire = []
	pointFree = []
	for row in reader:
		level.append(row['level'])
		machine.append(row['machine'])
		line.append(row['line'])
		maxBet.append(row['maxBet'])
		pointRequire.append(row['pointRequire'])
		pointFree.append(row['pointFree'])


# Bar progress, but not in use at the moment
def progress(end_val, bar_length=100):
    for i in xrange(0, end_val):
        percent = float(i) / end_val
        hashes = '#' * int(round(percent * bar_length))
        spaces = ' ' * (bar_length - len(hashes))
        sys.stdout.write("\rProcesando: [{0}] {1}%".format(hashes + spaces, int(round(percent * 100))))
        sys.stdout.flush()
    print('\nFinalizo')

# Read Simulator C OLD
def simulator(line, machine):
	process = 0
	process = os.popen('./sim_clean 1 ' + str(line)+' ' + str(machine) +' 1').read()
	return process
	

# Calc Money, FreeCoins, Levels of Simulator C
def money(coins):
	# moneySave = coins
	count = 1
	spent = 0
	spins = 0
	win = 0
	countMoneyWin = 0
	upLevel =  0
	maq = 1
	bet = 20
	nvl = 1
	spentRequire = 	pointRequire[count]
	while coins > 0:
		spins = spins + 1
		spent = bet + spent
		# print('Coins: ', coins, 'Spent: ', spent, 'Spins: ', count,'Level',nvl) 
		if spent in range(int(spentRequire), int(pointRequire[count + 1]) - 1):
			spent = int(line[pointRequire.index(spentRequire)])*int(maxBet[pointRequire.index(spentRequire)]) + spent
			maq = int(machine[pointRequire.index(spentRequire)])
			bet = int(line[pointRequire.index(spentRequire)])*int(maxBet[pointRequire.index(spentRequire)])
			nvl = int(level[pointRequire.index(spentRequire)])
			upLevel = int(pointFree[pointRequire.index(spentRequire)])
			count = count + 1
			if nvl == 8:
				break
			# print('='*10,'Nivel',count,'='*10)
		win = float(simulator(bet,maq).split()[1])
		a = int(maxBet[pointRequire.index(spentRequire)])
		coins = coins + win * a + upLevel - bet
		if coins < 0:
			coins = 0
		spentRequire = pointRequire[count]
		countMoneyWin = countMoneyWin + win
	#When Coins=0, Coins restart and  residue 1 user
	global coinSave
	global userCur
	coins = coinSave
	userCur = userCur - 1
	# Print Result
	print('Nivel alcanzado: ', nvl, ' | Giros Totales: ', spins, ' | Gano Total: ', countMoneyWin)



# Run Simulator with number of users and coins to init
def run(users, coins):
	moneyOriginal = coins	
	# Save Global Vars
	global userCur;
	global coinSave;
	userCur = users;
	coinSave = coins;
	#Loop users for coins
	while userCur > 0:
		money(coins)
	print('='*30, 'Finalizo', '='*30)

#Raw Input 
input_user = input("Cantidad de usuarios:")
input_money = input("Cantidad de monedas:")
if(input_money > 0):
	run(input_user, input_money)