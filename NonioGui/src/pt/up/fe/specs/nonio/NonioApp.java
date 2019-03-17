/**
 * Copyright 2019 SPeCS.
 * 
 * Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except in compliance with
 * the License. You may obtain a copy of the License at
 * 
 * http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software distributed under the License is distributed on
 * an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the License for the
 * specific language governing permissions and limitations under the License. under the License.
 */

package pt.up.fe.specs.nonio;

import java.io.File;
import java.util.ArrayList;
import java.util.List;

import org.lara.interpreter.joptions.config.interpreter.LaraiKeys;
import org.lara.interpreter.joptions.config.interpreter.VerboseLevel;
import org.lara.interpreter.joptions.keys.FileList;
import org.lara.interpreter.joptions.keys.OptionalFile;
import org.suikasoft.jOptions.DataStore.ADataClass;
import org.suikasoft.jOptions.Datakey.DataKey;
import org.suikasoft.jOptions.Datakey.KeyFactory;
import org.suikasoft.jOptions.Interfaces.DataStore;
import org.suikasoft.jOptions.app.App;
import org.suikasoft.jOptions.app.AppKernel;
import org.suikasoft.jOptions.storedefinition.StoreDefinition;

import larai.LaraI;
import pt.up.fe.specs.clava.weaver.CxxWeaver;
import pt.up.fe.specs.clava.weaver.options.CxxWeaverOption;
import pt.up.fe.specs.nonio.bundles.Compiler;
import pt.up.fe.specs.nonio.bundles.DseAlgorithm;
import pt.up.fe.specs.nonio.bundles.Language;
import pt.up.fe.specs.nonio.bundles.Metric;
import pt.up.fe.specs.nonio.bundles.Platform;
import pt.up.fe.specs.util.SpecsIo;
import pt.up.fe.specs.util.SpecsLogs;

public class NonioApp extends ADataClass<NonioApp> implements App, AppKernel {

    /// DATAKEYS BEGIN

    public static final DataKey<File> SOURCE_FILE = KeyFactory.file("Source File");
    public static final DataKey<Integer> N_STEPS = KeyFactory.integer("Number of steps").setDefault(() -> 100);
    public static final DataKey<Integer> SEQUENCE_LENGTH = KeyFactory.integer("Maximum sequence length")
            .setDefault(() -> 32);
    public static final DataKey<Compiler> COMPILER = KeyFactory.enumeration("Compiler", Compiler.class);
    public static final DataKey<Language> LANGUAGE = KeyFactory.enumeration("Language", Language.class);
    public static final DataKey<Platform> PLATFORM = KeyFactory.enumeration("Platform", Platform.class);
    public static final DataKey<DseAlgorithm> ALGORITHM = KeyFactory.enumeration("DSE Algorithm", DseAlgorithm.class);
    // AlgoExtra, when we have an option for JsonObject
    public static final DataKey<Integer> NUM_EXEC = KeyFactory.integer("Number of executions per sequence")
            .setDefault(() -> 1);
    public static final DataKey<Integer> MINIMUM_EXEC_FOR_REPORT = KeyFactory
            .integer("Minimum executions for reporting")
            .setDefault(() -> 1);
    public static final DataKey<Metric> METRICS = KeyFactory.enumeration("Metric", Metric.class);
    public static final DataKey<Boolean> ALREADY_INSTRUMENTED = KeyFactory.bool("Is already instrumented");
    public static final DataKey<Boolean> IS_VERIFICATION_SEPARATED = KeyFactory.bool("Is verification separated");
    public static final DataKey<String> LOG_FILE = KeyFactory.string("Log file (use .gz extension for compressed log)");
    public static final DataKey<Boolean> STORE_RESULTS = KeyFactory.bool("Store results");

    /// DATAKEYS END

    @Override
    public AppKernel getKernel() {
        return new NonioApp();
    }

    @Override
    public StoreDefinition getDefinition() {
        return getDataStore().getStoreDefinition().get();
    }

    @Override
    public int execute(DataStore options) {
        Nonio nonio = new Nonio();

        // Source file must be defined
        File sourceFile = options.get(SOURCE_FILE);
        if (!sourceFile.isFile()) {
            SpecsLogs.info("Source file must be defined");
            return 1;
        }

        // var laradFile = argPath(laradFoldername, "Larad.lara");
        // var laradFolder = argPath(laradFoldername);
        // var dseLaraFolder = argPath(laradFoldername, "lara");
        // var dseBundleFolder = argPath(laradFoldername, "bundles");
        // var pathSeparator = Io.getPathSeparator();

        // Prepare DataStore for Nonio run
        DataStore clavaData = DataStore.newInstance("Nonio data");

        // Default options
        clavaData.put(LaraiKeys.VERBOSE, VerboseLevel.warnings);
        clavaData.set(LaraiKeys.TRACE_MODE);
        clavaData.set(CxxWeaverOption.DISABLE_WEAVING);

        clavaData.put(LaraiKeys.LARA_FILE, nonio.getMainAspect());

        String aspectArgs = "{laradFoldername:'" + SpecsIo.normalizePath(nonio.getNonioFolder()) + "', compiler:'"
                + options.get(COMPILER).getKey() + "', compilerFolderName:undefined, compilerPrefix:''";

        aspectArgs += ", sourceFile:'" + SpecsIo.normalizePath(sourceFile) + "'";

        aspectArgs += ", nsteps:" + options.get(N_STEPS);

        aspectArgs += ", seqlen:" + options.get(SEQUENCE_LENGTH);

        aspectArgs += ", metrics: ['" + options.get(METRICS).getKey() + "']";

        aspectArgs += ", language: '" + options.get(LANGUAGE).getKey() + "'";

        aspectArgs += ", alreadyInstrumented: " + options.get(ALREADY_INSTRUMENTED);

        aspectArgs += ", isVerificationSeparated: " + options.get(IS_VERIFICATION_SEPARATED);

        aspectArgs += ", nexec: " + options.get(NUM_EXEC);

        aspectArgs += ", minimumExecForReporting: " + options.get(MINIMUM_EXEC_FOR_REPORT);

        aspectArgs += ", specialLinker: 'undefined'";

        aspectArgs += ", target: '" + options.get(PLATFORM).getKey() + "'";

        aspectArgs += ", storeResults: '" + options.get(STORE_RESULTS) + "'";

        // aspectArgs += ", algoExtra: '" + algoExtra + "'";

        aspectArgs += "}";

        clavaData.put(LaraiKeys.ASPECT_ARGS, aspectArgs);

        SpecsLogs.debug("Aspect arguments for Nonio: " + aspectArgs);

        // Includes

        List<File> includes = new ArrayList<>();
        includes.add(nonio.getNonioFolder());
        includes.add(nonio.getDseLaraFolder());
        includes.add(nonio.getCompilersBundleFolder());
        includes.add(nonio.getAlgorithmsBundleFolder());
        includes.add(nonio.getPlatformsBundleFolder());
        includes.add(nonio.getLanguagesBundleFolder());
        includes.add(nonio.getIncludeScriptsFolder());

        clavaData.put(LaraiKeys.INCLUDES_FOLDER, FileList.newInstance(includes));

        String logFilename = options.get(LOG_FILE).trim();
        if (!logFilename.isEmpty()) {
            clavaData.put(LaraiKeys.LOG_FILE, OptionalFile.newInstance(logFilename));

            // If log file is set, add -j
            clavaData.set(LaraiKeys.LOG_JS_OUTPUT);
        }

        String bundles = "compiler=" + options.get(COMPILER).getKey()
                + ",algo=" + options.get(ALGORITHM).getKey()
                + ",language=" + options.get(LANGUAGE).getKey()
                + ",platform=" + options.get(PLATFORM).getKey();

        clavaData.put(LaraiKeys.BUNDLE_TAGS, bundles);
        // System.out.println("CLAVA DATA:" + clavaData);
        boolean success = LaraI.exec(clavaData, new CxxWeaver());

        return success ? 0 : 1;
    }

}
