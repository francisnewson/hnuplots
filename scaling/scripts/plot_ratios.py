import matplotlib.pyplot as plt
import matplotlib as mpl
import pandas as pd

m2m_data = pd.read_csv('data/test_m2m.dat', delim_whitespace = True )


fig = plt.figure( figsize = [8, 6] )
fig.set_tight_layout(True)
ax = fig.add_subplot( 111 )

ax.grid( 'on' )
ax.set_xlabel( '$m^2_\\textrm{miss}$ cut $(\\unit[]{GeV^2/c^4)}$')

x = m2m_data['mod_mass']
y = m2m_data['pos_ratio']
yerr = m2m_data['pos_ratio_err']

ax.errorbar( m2m_data['mod_mass'], m2m_data['pos_ratio'], yerr = m2m_data['pos_ratio_err'], 
        fmt = '-o', mec = 'None', color = 'k' )

plt.savefig( 'output/m2m_pos.pdf', format = 'pdf', transparent = 'true' )

plt.cla()

ax.grid( 'on' )
ax.set_xlabel( '$m^2_\\textrm{miss}$ cut $(\\unit[]{GeV^2/c^4)}$')

ax.fill_between( x, y - yerr, y + yerr, facecolor = 'gray', edgecolor = "None" )
ax.plot( x, y , color = 'k' )

plt.savefig( 'output/m2m_pos_fill.pdf', format = 'pdf', transparent = 'true' )
