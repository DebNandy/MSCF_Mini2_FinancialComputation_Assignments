# -*- coding: utf-8 -*-
"""
Created on Sun Dec  2 16:38:12 2018

@author: shuva
Financial Computing II
"""
#Authors:
# DEBAJYOTI NANDY
# AVINASH SHRIVASTAVA
# PALLAV RAJ


infile = open('cme.20180320.c.pa2', 'r')
outfile = open('CL_and_NG_expirations_and_settlements.txt', 'w')

outfile.writelines('Futures   Contract   Contract   Futures     Options   Options\n')
outfile.writelines('Code      Month      Type       Exp Date    Code      Exp Date\n')
outfile.writelines('-------   --------   --------   --------    -------   --------\n')
limit_print = 0
for line in infile:
    rec_type = line[:2]
    if rec_type =='B ':
        futures_code = line[99:102]
        contract_code_first_3 = line[5:8];	
        if (futures_code == 'CL ' and (contract_code_first_3 == 'CL ' or contract_code_first_3 == 'LO ')) or (futures_code == "NG " and (contract_code_first_3 == "NG " or contract_code_first_3 == "ON ")):
            contract_month = line[18:24]
            if contract_month >= '201807' and contract_month <= '202012':
                contract_month = contract_month[:4]+'-'+contract_month[4:]
                fut_exp_date = ''
                option_code = ''
                options_exp_date = ''
                if line[15:18] == 'FUT':
                    contract_type = 'Fut'
                    fut_exp_date = line[91:99]
                    fut_exp_date = fut_exp_date[:4]+'-'+fut_exp_date[4:6]+'-'+fut_exp_date[6:]
                elif line[15:18] == 'OOF' and (contract_code_first_3 == 'LO ' or contract_code_first_3 == 'ON '):
                    contract_type = 'Opt'
                    options_exp_date = line[91:99]
                    options_exp_date = options_exp_date[:4] + '-' + options_exp_date[4:6]+ '-' + options_exp_date[6:];
                    option_code = contract_code_first_3[:2]
                outfile.writelines('{:<10}'.format(futures_code) + 
                               '{:<11}'.format(contract_month) + 
                               '{:<11}'.format(contract_type) + 
                               '{:<12}'.format(fut_exp_date) + 
                               '{:<10}'.format(option_code) + 
                               '{:<8}'.format(options_exp_date) +'\n')
outfile.writelines('Futures   Contract   Contract   Strike   Settlement\n')
outfile.writelines('Code      Month      Type       Price    Price\n')
outfile.writelines('-------   --------   --------   ------   ----------\n')
infile.seek(0)
for line in infile:
    rec_type = line[:2]
    if rec_type == '81':
        CL_tick_size = 0.01
        NG_tick_size = 0.001
        NG_futures_fudge_factor = 0.01
        NG_options_fudge_factor = 0.1
        futures_code = line[15:18]
        contract_code_first_3 = line[5:8];	
        if (futures_code == 'CL ' and (contract_code_first_3 == 'CL ' or contract_code_first_3 == 'LO ')) or (futures_code == "NG " and (contract_code_first_3 == "NG " or contract_code_first_3 == "ON ")):
            contract_month = line[29:35]
            if contract_month >= '201807' and contract_month <= '202012':
                contract_month = contract_month[:4]+'-'+contract_month[4:]
                C_or_P = line[28]
                strike_price_ticks = float(line[47:54])
                settlement_price_ticks = float(line[108:122])
                strike_price = -1.0 #initially bogus
                settlement_price = -1.0 #initially bogus
                if line[25:28] == 'FUT':
                    contract_type = 'Fut'
                    if futures_code == 'CL ':
                        settlement_price = '{:.2f}'.format(settlement_price_ticks * CL_tick_size)
                    else :
                         settlement_price = '{:.3f}'.format(settlement_price_ticks * NG_tick_size * NG_futures_fudge_factor);
                    outfile.writelines('{:<10}'.format(futures_code) + 
                               '{:<11}'.format(contract_month) + 
                               '{:<11}'.format(contract_type) + 
                               '{:<7}'.format('') +
                               '{:>10}'.format(settlement_price) + '\n')
                elif line[25:28] == 'OOF' :
                    if C_or_P == 'C' :
                        contract_type = 'Call'
                    else :
                        contract_type = 'Put'
                    if futures_code == 'CL ':
                        strike_price = '{:.2f}'.format(strike_price_ticks * CL_tick_size)
                        settlement_price = '{:.2f}'.format(settlement_price_ticks * CL_tick_size)
                    else :
                        strike_price = '{:.3f}'.format(strike_price_ticks * NG_tick_size)
                        settlement_price = '{:.3f}'.format(settlement_price_ticks * NG_tick_size * NG_options_fudge_factor)
                    contract_type = 'Opt'
                    outfile.writelines('{:<10}'.format(futures_code) + 
                               '{:<11}'.format(contract_month) + 
                               '{:<11}'.format(contract_type) + 
                               '{:<7}'.format(strike_price) +
                               '{:>10}'.format(settlement_price) + '\n')    
infile.close()
outfile.close() 