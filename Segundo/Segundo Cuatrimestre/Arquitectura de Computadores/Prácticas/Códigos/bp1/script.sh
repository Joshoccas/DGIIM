#!/bin/bash
#!/bin/bash
#Órdenes para el Gestor de carga de trabajo (no intercalar instrucciones del scrip
#1. Asignar al trabajo un nombre
#SBATCH --job-name=helloOMP
#2. Asignar el trabajo a una partición (cola) 
#SBATCH --partition=ac
#3. Asignar el trabajo a un account 
#SBATCH --account=ac
#4. Para que el trabajo no comparta recursos 
#SBATCH --exclusive
#5. Para que se genere un único proceso del sistema operativo que pueda usar un máximo de 12 núcleos
#SBATCH --ntasks 1 --cpus-per-task 12
#Se pueden añadir más órdenas para el gestor de colas

#Obtener información de las variables del entorno del Gestor de carga de trabajo:
echo "Id. usuario del trabajo: $SLURM_JOB_USER"
echo "Id. del trabajo: $SLURM_JOBID"
echo "Nombre del trabajo especificado por usuario: $SLURM_JOB_NAME"
echo "Directorio de trabajo (en el que se ejecuta el script): $SLURM_SUBMIT_DIR"
echo "Cola: $SLURM_JOB_PARTITION"
echo "Nodo que ejecuta este trabajo:$SLURM_SUBMIT_HOST"
echo "Nº de nodos asignados al trabajo: $SLURM_JOB_NUM_NODES"
echo "Nodos asignados al trabajo: $SLURM_JOB_NODELIST"
echo "CPUs por nodo: $SLURM_JOB_CPUS_PER_NODE"

for (( CONTADOR=65536; CONTADOR<=67108864; CONTADOR*=2)) ; do
  srun ./SumaVectores $CONTADOR >> salida.dat
done

for (( CONTADOR=65536; CONTADOR<=67108864; CONTADOR*=2)) ; do
  srun ./sp-OpenMP-for $CONTADOR >> salida_for.dat
done

for (( CONTADOR=65536; CONTADOR<=67108864; CONTADOR*=2)) ; do
  srun ./sp-OpenMP-sections $CONTADOR >> salida_sections.dat
done


