#!/bin/bash

# Créer nouvelle branche propre
git checkout --orphan temp_branch
git add -A
git commit -m "Initial commit" --author="Jeremie Villepreux <jrmiepreux@yahoo.fr>"

# Remplacer master
git branch -D master
git branch -m master

# Configurer nouveau remote
git remote remove origin
git remote add origin git@github.com:jeremieCode/jpegEncoder.git

# Push force
git push -f origin master