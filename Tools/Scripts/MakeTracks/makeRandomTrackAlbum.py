import randomtrack

for i in range(12):
    fn = "rand_%04d.png" % i

    randomtrack.makeTrack(25, fn)
