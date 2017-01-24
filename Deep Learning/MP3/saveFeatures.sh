#!/bin/bash
# This script runs multiple batch jobs to test different hyperparameter
# settings. For each setting, it creates a different PBS file and calls
# it.

# MODIFY THESE
declare training_file="saveFeatures_1024.py"
declare walltime="02:30:00"
declare jobname="saveFeaturesPredictions"
declare netid="courtne2"

# Declare the hyperparameters you want to iterate over
declare -a dataset_batch_number=(0 1 2 3 4 5 6 7 8 9 10 11)

# For each parameter setting we generate a new PBS file and run it
for batch_no in "${dataset_batch_number[@]}"
do
  python generate_pbs.py $training_file $walltime $jobname $netid $batch_no > run.pbs
  echo "Submitting $batch_no"
  qsub run.pbs
done
