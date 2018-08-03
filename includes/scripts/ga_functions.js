// =====================================================================================
// General Functions
// =====================================================================================

	// 1D Array initialization
	Array.init = function (dim, initValue) {
		var a = [], i;
		for (i = 0; i < dim; i++) {
			a[i] = initValue;
		}
		return a;
	};

	// Argument of object.sort() - extended version for minimization
	var by = function (name, minor) {
		return function (o, p) {
			var a, b;
			if (o && p && typeof o === 'object' && typeof p === 'object' ) {
				a = o[name];
				b = p[name];
				if (a === b) {
					return typeof minor === 'function' ? minor(o,p) : 0;
				}
				if (typeof a === typeof b) {
					return a < b ? -1 : 1;
				}
				return typeof a < typeof b ? -1 : 1;
			}
			else {
				throw {
					name: 'Error',
					message: 'Expected an object when sorting by ' + name
				};
			};
		};
	};

	// Argument of object.sort() - extended version for maximization
	var py = function (name, major) {
		return function (o, p) {
			var a, b;
			if (o && p && typeof o === 'object' && typeof p === 'object' ) {
				a = o[name];
				b = p[name];
				if (a === b) {
					return typeof major === 'function' ? major(o,p) : 0;
				}
				if (typeof a === typeof b) {
					return a > b ? -1 : 1;
				}
				return typeof a > typeof b ? -1 : 1;
			}
			else {
				throw {
					name: 'Error',
					message: 'Expected an object when sorting by ' + name
				};
			};
		};
	};

	// Specific optimization counter function
	var count = function (chromo, elem) {
		var counterElem = 0;
		var size = chromo.length;
		var idx;
		
		for (idx=0; idx < size; idx++) {
			if (chromo[idx] == elem) {
				counterElem++;
			};
		};
		
		return counterElem;
	};

/*	// Finder (recursive)
	var find = function (chromo, pos, elem) {
		if (pos >= chromo.length) {
			return -1;
		};
		return (chromo[pos] == elem ? pos : find(chromo, pos+1, elem));
	};
/**/
	// Finder (interactive)
	var find = function (chromo, pos, elem) {
		var idx;
		var size = chromo.length;
		for (idx = pos; idx < size; idx++) {
			if (chromo[pos] == elem) {
				return (pos);
			};
		};
		return (-1);
	};

	// Write content in text file (write)
	function writeFile(path, content) {
	    var file = new java.io.File(path);
		Java.type('pt.up.fe.specs.util.SpecsIo').write(file,content);
	}

	// Write content in text file (append)
	function appendFile(path, content) {
	    var file = new java.io.File(path);
	    Java.type('pt.up.fe.specs.util.SpecsIo').append(file,content);
	}
// =====================================================================================
// Specific Functions
// =====================================================================================

	// Individual maker
	var indiv_maker = function () {
		// Individual representation
		return {
			chromosome: [],
			chromosomeSize: 0,
			loopFactors: [],
			fitness: undefined
		};
	};

	// Individual copier
	var indiv_copy = function (source) {
		var sink = indiv_maker();
		sink.chromosome = source.chromosome.slice(0);
		sink.chromosomeSize = source.chromosomeSize;
		sink.loopFactors = source.loopFactors.slice(0);
		sink.fitness = source.fitness;
		
		return sink;
	};

	// Individual finder
	var indiv_finder = function (base, indiv) {
		var size = base.length;
		var x;
		for (x=0; x < size; x++) {
			if (base[x].chromosome.join(",") == indiv.chromosome.join(",") && base[x].loopFactors.join(",") == indiv.loopFactors.join(","))
				return x;
		};
		
		return -1;
	};

	// Fitness finder
	var fitness_finder = function (base, indiv_fit) {
		var size = base.length;
		var x;
		for (x=0; x < size; x++) {
			if (base[x].fitness == indiv_fit)
				return x;
		};
		
		return -1;
	};
	
	// Tournament function (Sorted Array Version)
	var tournament = function (indiv, size, qty) {
		var counter;
		var bestId = Math.floor(Math.random()*(size-0.1));
		
		for (counter = 1; counter < qty; counter++) {
			var idx = Math.floor(Math.random()*(size-0.1));
			if (idx < bestId) {
				bestId  = idx;
			};
		};
		
		return (bestId);
	};

	//------------------------------------------------------------------------------------------------------------
	// Mutation function for chromosome with fixed size
	var fixedmutation = function (loopranks_size, loopfactors, optimizations, indiv, flag_unroll) {
		var factor = Math.random();
		var loopfactors_size = loopfactors.length;
		var point;

		if (flag_unroll == 0) {
			// Mutation over transformation
			indiv.chromosome[optimizations] = !indiv.chromosome[optimizations];
		}
		else {
			// Mutation over transformation
			if (factor > 0.4) {
				indiv.chromosome[optimizations] = !indiv.chromosome[optimizations];
			};
		
			// Mutation over unrolling factor
	                if (factor < 0.6) {
		               	var newPt = Math.floor(Math.random()*(loopfactors_size-0.1));
				point = Math.floor(Math.random()*(loopranks_size-0.1));
				indiv.loopFactors[point] = loopfactors[newPt];
			};
		};

		return 1;
	};
	//------------------------------------------------------------------------------------------------------------
	
	//------------------------------------------------------------------------------------------------------------
	// Mutation function for chromosome with variable size
	var mutation = function (loopranks_size, loopfactors, optimizations, indiv, maxpoint, flag_unroll, maxwidth) {
		var factor = Math.random();
		var loopfactors_size = loopfactors.length;
		var point;

		// Mutation over unrolling factor
                if ((flag_unroll > 0) && (factor >= 0.6)) {
	               	var newPt = Math.floor(Math.random()*loopfactors_size);
			point = Math.floor(Math.random()*loopranks_size);
			indiv.loopFactors[point] = loopfactors[newPt];
		}
		else {
			factor = factor * 0.85; // It limits the factor range from 0 to 0.85
		};

		// Mutation over transformation
		if (factor <= 0.85) {
			// Choose the gene for mutation
			if (maxpoint > 1) {
				point = Math.floor(Math.random()*(maxpoint-1.1));
			}
			else {
				point = 0;
			}

			// Choose perturbation method randomly
			if (factor <= 0.25) { // insert new optimization into individual chromosome
				if (maxpoint < maxwidth) {
					indiv.chromosome.splice(point,0,optimizations);
				}
				else {
					indiv.chromosome[point] = optimizations; // Change an optimization randomly
				};
			}

			else if (factor > 0.25 && factor <= 0.5) { // swap two array positions
				if (maxpoint > 1) {
					var newPt;
		              		newPt = Math.floor(Math.random()*(maxpoint-1.1));
					if (point == newPt) {
						newPt = (newPt+1)%maxpoint;
					};
						
					var temporary = indiv.chromosome[point];
					indiv.chromosome[point] = indiv.chromosome[newPt];
					indiv.chromosome[newPt] = temporary;
				}
				else { // There is one or zero optimization in individual
					indiv.chromosome[maxpoint] = optimizations; // insert new optimization
				}
			}

			else if (factor > 0.5 && factor <= 0.75) { // Change an optimization randomly chosen in the array position
	                       	indiv.chromosome[point] = optimizations;
			}

			else { // remove an individual's optimization
	    			indiv.chromosome.splice(point,1);
			};
		};

		return 1;
	};
	//------------------------------------------------------------------------------------------------------------

