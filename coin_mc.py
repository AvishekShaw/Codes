
import numpy as np
import matplotlib.pyplot as plt
import seaborn as sns

# Game 1
simulations = 10000  # number of Monte Carlo Simulations
games = 100          # number of times the game is played
threshold = 40       # threshold where if greater than or equal to you win
bet = 1              # dollar bet for the game

# outer loop is Monte Carlo sims and inner loop is games played
sim_results_1 = []
for sim in range(simulations):
    result = []
    for g in range(games):
        number = int(np.random.uniform()*100)  # get a random number to see who wins
        if number >= threshold:
            result.append(bet)
        else:
            result.append(-bet)
    sim_results_1.append(sum(result))          # sim_results_1 stores results for Game 1
print('Game 1 Mean: ', round(np.mean(sim_results_1), 2))
print('Game 1 Prob Positive: ', round(sum([1 for i in sim_results_1 if i>0])/simulations, 2))
print('\n')
    

# Game 2 (structure of code is same as above)
simulations = 10000
games = 10
threshold = 40
bet = 10

sim_results_2 = []
for sim in range(simulations):
    result = []
    for g in range(games):
        number = int(np.random.uniform()*100)
        if number >= threshold:
            result.append(bet)
        else:
            result.append(-bet)
    sim_results_2.append(sum(result))
print('Game 2 Mean: ', round(np.mean(sim_results_2), 2))
print('Game 2 Prob Positive: ', round(sum([1 for i in sim_results_2 if i>0])/simulations, 2))
print('\n')
    
    
# Game 3 (structure of code is same as above)
simulations = 10000
games = 1
threshold = 40
bet = 100

sim_results_3 = []
for sim in range(simulations):
    result = []
    for g in range(games):
        number = int(np.random.uniform()*100)
        if number >= threshold:
            result.append(bet)
        else:
            result.append(-bet)
    sim_results_3.append(sum(result))
print('Game 3 Mean: ', round(np.mean(sim_results_3), 2))
print('Game 3 Prob Positive: ', round(sum([1 for i in sim_results_3 if i>0])/simulations, 2))


# Histogram that shows the distribution of the Monte Carlo Results for 2 spending levels
fig, ax = plt.subplots(figsize=(8,6))
sns.distplot(sim_results_1, kde=False, bins=60, label='Play 100 Times')
sns.distplot(sim_results_2, kde=False, bins=60, label='Play 10 Times')
sns.distplot(sim_results_3, kde=False, bins=60, label='Play 1 Time', color='pink')

ax.set_xlabel('Money Won by You (The Player)', fontsize=16)
ax.set_ylabel('Frequency',fontsize=16)
plt.legend()
plt.tight_layout()

plt.savefig(fname='game_hist', dpi=150)
plt.show()

'''Game 1 Mean:  20.04
Game 1 Prob Positive:  0.97


Game 2 Mean:  20.13
Game 2 Prob Positive:  0.63


Game 3 Mean:  19.08
Game 3 Prob Positive:  0.6

In [ ]:
'''